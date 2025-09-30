import pandas as pd
import matplotlib.pyplot as plt

csv_data = r'C:\Users\lucas\OneDrive\Documentos\Faculdade\_CADEIRAS\11 semestre\Processamento Digital de Sinais\Labs\Lab 01 - media movel\Download Data - STOCK_BR_BVMF_PETR3.csv'

# --- PARÂMETROS GLOBAIS DA SIMULAÇÃO ---
CAPITAL_INICIAL = 1000.00
PERIODO_MEDIA_MOVEL = 4
DIAS_TENDENCIA = 3

def carregar_dados():
    try:
        # Use io.StringIO para ler a string como se fosse um arquivo
        df = pd.read_csv(csv_data, sep=',', parse_dates=['Date'], on_bad_lines='skip')
    except Exception as e:
        print(f"ERRO ao carregar os dados: {e}")
        return None
    
    # Limpeza e preparação dos dados
    df['Volume'] = df['Volume'].str.replace(',', '').str.replace('_','').astype(float)
    df = df.sort_values(by='Date').reset_index(drop=True)
    df = df[['Date', 'Close']]
    
    # Cálculo do indicador de média móvel
    df['media_movel'] = df['Close'].rolling(window=PERIODO_MEDIA_MOVEL).mean()
    df.dropna(inplace=True) # Remove linhas iniciais sem média móvel
    df = df.reset_index(drop=True) # Reseta o índice após o dropna
    
    return df

def simular_solucao_1(df, capital_inicial):
    print("--- INICIANDO SIMULAÇÃO (SOLUÇÃO 1: Tendência de 3 dias) ---")
    capital = capital_inicial
    quantidade_acoes = 0
    historico_transacoes = []
    portfolio_diario = []

    for i in range(len(df)):
        # --- Lógica de Decisão ---
        is_primeiro_dia = (i == 0)
        is_ultimo_dia = (i == len(df) - 1)
        
        preco_hoje = df['Close'].iloc[i]
        data_hoje = df['Date'].iloc[i]
        
        # --- COMPRA OBRIGATÓRIA (PRIMEIRO DIA) ---
        if is_primeiro_dia:
            acoes_a_comprar = capital / preco_hoje
            quantidade_acoes = acoes_a_comprar
            capital = 0
            transacao = {'Date': data_hoje, 'Operacao': 'COMPRA', 'Preco': preco_hoje}
            historico_transacoes.append(transacao)
            print(f"COMPRA (Obrigatória): {acoes_a_comprar:.4f} ações a R$ {preco_hoje:.2f} em {data_hoje.strftime('%Y-%m-%d')}")
        
        # --- VENDA OBRIGATÓRIA (ÚLTIMO DIA) ---
        elif is_ultimo_dia:
            if quantidade_acoes > 0:
                capital += quantidade_acoes * preco_hoje
                transacao = {'Date': data_hoje, 'Operacao': 'VENDA', 'Preco': preco_hoje}
                historico_transacoes.append(transacao)
                print(f"VENDA (Obrigatória):  {quantidade_acoes:.4f} ações a R$ {preco_hoje:.2f} em {data_hoje.strftime('%Y-%m-%d')}")
                quantidade_acoes = 0
        
        # --- LÓGICA DE TENDÊNCIA (DIAS INTERMEDIÁRIOS) ---
        elif i >= DIAS_TENDENCIA:
            preco_ontem = df['Close'].iloc[i-1]
            preco_anteontem = df['Close'].iloc[i-2]
            preco_tres_dias_atras = df['Close'].iloc[i-3]
            
            tendencia_de_queda = (preco_ontem < preco_anteontem) and (preco_anteontem < preco_tres_dias_atras)
            tendencia_de_alta = (preco_ontem > preco_anteontem) and (preco_anteontem > preco_tres_dias_atras)
            
            if tendencia_de_queda and capital > 0:
                acoes_a_comprar = capital / preco_hoje
                quantidade_acoes += acoes_a_comprar
                capital = 0
                transacao = {'Date': data_hoje, 'Operacao': 'COMPRA', 'Preco': preco_hoje}
                historico_transacoes.append(transacao)
                print(f"COMPRA: {acoes_a_comprar:.4f} ações a R$ {preco_hoje:.2f} em {data_hoje.strftime('%Y-%m-%d')}")
            
            elif tendencia_de_alta and quantidade_acoes > 0:
                capital += quantidade_acoes * preco_hoje
                transacao = {'Date': data_hoje, 'Operacao': 'VENDA', 'Preco': preco_hoje}
                historico_transacoes.append(transacao)
                print(f"VENDA:  {quantidade_acoes:.4f} ações a R$ {preco_hoje:.2f} em {data_hoje.strftime('%Y-%m-%d')}")
                quantidade_acoes = 0
        
        # Atualiza o valor do portfólio no final de cada dia
        valor_portfolio_hoje = capital + (quantidade_acoes * preco_hoje)
        portfolio_diario.append(valor_portfolio_hoje)

    # --- Cálculo dos Resultados Finais ---
    df['Portfolio'] = portfolio_diario
    valor_final = df['Portfolio'].iloc[-1]
    lucro = valor_final - capital_inicial
    rentabilidade = (lucro / capital_inicial) * 100
    
    print("--- SIMULAÇÃO 1 FINALIZADA ---\n")
    resultados = {"valor_final": valor_final, "lucro": lucro, "rentabilidade": rentabilidade}
    return resultados, df, historico_transacoes


def simular_solucao_2(df, capital_inicial):
    print("--- INICIANDO SIMULAÇÃO (SOLUÇÃO 2: Cruzamento de Média Móvel) ---")
    capital = capital_inicial
    quantidade_acoes = 0
    em_posicao = False
    historico_transacoes = []
    portfolio_diario = []

    for i in range(len(df)):
        # --- Lógica de Decisão ---
        is_primeiro_dia = (i == 0)
        is_ultimo_dia = (i == len(df) - 1)
        
        linha_atual = df.iloc[i]
        preco_hoje = linha_atual['Close']
        data_hoje = linha_atual['Date']

        # --- COMPRA OBRIGATÓRIA (PRIMEIRO DIA) ---
        if is_primeiro_dia:
            acoes_a_comprar = capital / preco_hoje
            quantidade_acoes = acoes_a_comprar
            capital = 0
            em_posicao = True
            transacao = {'Date': data_hoje, 'Operacao': 'COMPRA', 'Preco': preco_hoje}
            historico_transacoes.append(transacao)
            print(f"COMPRA (Obrigatória): {acoes_a_comprar:.4f} ações a R$ {preco_hoje:.2f} em {data_hoje.strftime('%Y-%m-%d')}")

        # --- VENDA OBRIGATÓRIA (ÚLTIMO DIA) ---
        elif is_ultimo_dia:
            if quantidade_acoes > 0:
                capital += quantidade_acoes * preco_hoje
                transacao = {'Date': data_hoje, 'Operacao': 'VENDA', 'Preco': preco_hoje}
                historico_transacoes.append(transacao)
                print(f"VENDA (Obrigatória):  {quantidade_acoes:.4f} ações a R$ {preco_hoje:.2f} em {data_hoje.strftime('%Y-%m-%d')}")
                quantidade_acoes = 0
        
        # --- LÓGICA DE CRUZAMENTO (DIAS INTERMEDIÁRIOS) ---
        elif i > 0:
            linha_anterior = df.iloc[i-1]
            sinal_compra = (linha_anterior['Close'] < linha_anterior['media_movel']) and (preco_hoje > linha_atual['media_movel'])
            sinal_venda = (linha_anterior['Close'] > linha_anterior['media_movel']) and (preco_hoje < linha_atual['media_movel'])

            if sinal_compra and not em_posicao:
                acoes_a_comprar = capital / preco_hoje
                quantidade_acoes = acoes_a_comprar
                capital = 0
                em_posicao = True
                transacao = {'Date': data_hoje, 'Operacao': 'COMPRA', 'Preco': preco_hoje}
                historico_transacoes.append(transacao)
                print(f"COMPRA: {acoes_a_comprar:.4f} ações a R$ {preco_hoje:.2f} em {data_hoje.strftime('%Y-%m-%d')}")
            
            elif sinal_venda and em_posicao:
                capital += quantidade_acoes * preco_hoje
                quantidade_acoes = 0
                em_posicao = False
                transacao = {'Date': data_hoje, 'Operacao': 'VENDA', 'Preco': preco_hoje}
                historico_transacoes.append(transacao)
                print(f"VENDA:  {quantidade_acoes:.4f} ações a R$ {preco_hoje:.2f} em {data_hoje.strftime('%Y-%m-%d')}")

        # Atualiza o valor do portfólio no final de cada dia
        valor_portfolio_hoje = capital + (quantidade_acoes * preco_hoje)
        portfolio_diario.append(valor_portfolio_hoje)

    # --- Cálculo dos Resultados Finais ---
    df['Portfolio'] = portfolio_diario
    valor_final = df['Portfolio'].iloc[-1]
    lucro = valor_final - capital_inicial
    rentabilidade = (lucro / capital_inicial) * 100

    print("--- SIMULAÇÃO 2 FINALIZADA ---\n")
    resultados = {"valor_final": valor_final, "lucro": lucro, "rentabilidade": rentabilidade}
    return resultados, df, historico_transacoes

def plotar_operacoes(df, transacoes, titulo):
    """Gera o gráfico de preços e pontos de compra/venda."""
    plt.style.use('seaborn-v0_8-whitegrid')
    plt.figure(figsize=(15, 7))
    
    plt.plot(df['Date'], df['Close'], label='Preço de Fechamento', color='skyblue', alpha=0.8)
    plt.plot(df['Date'], df['media_movel'], label=f'Média Móvel {PERIODO_MEDIA_MOVEL} Dias', color='orange', linestyle='--')
    
    compras = [t for t in transacoes if t['Operacao'] == 'COMPRA']
    vendas = [t for t in transacoes if t['Operacao'] == 'VENDA']
    
    datas_compra = [t['Date'] for t in compras]
    precos_compra = [t['Preco'] for t in compras]
    
    datas_venda = [t['Date'] for t in vendas]
    precos_venda = [t['Preco'] for t in vendas]
    
    plt.scatter(datas_compra, precos_compra, label='Pontos de Compra', marker='^', color='green', s=120, zorder=5)
    plt.scatter(datas_venda, precos_venda, label='Pontos de Venda', marker='v', color='red', s=120, zorder=5)
    
    plt.title(titulo, fontsize=16)
    plt.xlabel('Data')
    plt.ylabel('Preço (R$)')
    plt.legend()

def plotar_evolucao_portfolio(df, capital_inicial, titulo):
    """Gera o gráfico da evolução do valor do portfólio."""
    plt.style.use('seaborn-v0_8-whitegrid')
    plt.figure(figsize=(15, 5))
    
    plt.plot(df['Date'], df['Portfolio'], label='Valor do Portfólio', color='purple')
    plt.axhline(y=capital_inicial, color='red', linestyle='--', label=f'Capital Inicial (R$ {capital_inicial:,.2f})')
    
    plt.title(titulo, fontsize=16)
    plt.xlabel('Data')
    plt.ylabel('Valor (R$)')
    plt.legend()

# --- BLOCO PRINCIPAL DE EXECUÇÃO ---
if __name__ == "__main__":
    dataframe_base = carregar_dados()
    
    if dataframe_base is not None:
        resultados_1, df_hist_1, transacoes_1 = simular_solucao_1(dataframe_base.copy(), CAPITAL_INICIAL)
        resultados_2, df_hist_2, transacoes_2 = simular_solucao_2(dataframe_base.copy(), CAPITAL_INICIAL)
        
        # Apresenta a tabela de comparação
        print("="*60)
        print(" " * 18 + "PAINEL COMPARATIVO DE ESTRATÉGIAS")
        print("="*60)
        print(f"{'Métrica':<25} | {'Solução 1 (Tendência)':>15} | {'Solução 2 (Média Móvel)':>20}")
        print("-"*60)
        print(f"{'Capital Inicial (R$)':<25} | {CAPITAL_INICIAL:>15,.2f} | {CAPITAL_INICIAL:>20,.2f}")
        print(f"{'Valor Final (R$)':<25} | {resultados_1['valor_final']:>15,.2f} | {resultados_2['valor_final']:>20,.2f}")
        print(f"{'Lucro/Prejuízo (R$)':<25} | {resultados_1['lucro']:>15,.2f} | {resultados_2['lucro']:>20,.2f}")
        print(f"{'Rentabilidade (%)':<25} | {resultados_1['rentabilidade']:>14.2f}% | {resultados_2['rentabilidade']:>19.2f}%")
        print("="*60)
        
        # Gerar e exibir os gráficos
        plotar_operacoes(df_hist_1, transacoes_1, 'Simulação de Trading - Solução 1')
        plotar_evolucao_portfolio(df_hist_1, CAPITAL_INICIAL, 'Evolução do Portfólio - Solução 1')
        
        plotar_operacoes(df_hist_2, transacoes_2, 'Simulação de Trading - Solução 2')
        plotar_evolucao_portfolio(df_hist_2, CAPITAL_INICIAL, 'Evolução do Portfólio - Solução 2')

        plt.show()
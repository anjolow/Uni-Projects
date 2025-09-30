import pandas as pd
import matplotlib.pyplot as plt

# --- PARÂMETROS DA SIMULAÇÃO ---
ARQUIVO_CSV = r'C:\Users\lucas\OneDrive\Documentos\Faculdade\_CADEIRAS\11 semestre\Processamento Digital de Sinais\Labs\Lab 01 - media movel\Download Data - STOCK_BR_BVMF_PETR3.csv'
CAPITAL_INICIAL = 1000.00
PERIODO_MEDIA_MOVEL = 4
DIAS_TENDENCIA = 3 # Regra para avaliar a tendência de preço

# --- Carregamento e Tratamento dos Dados ---
try:
    df = pd.read_csv(ARQUIVO_CSV, sep=',', parse_dates=['Date'])
except FileNotFoundError:
    print(f"ERRO: Arquivo não encontrado em '{ARQUIVO_CSV}'. Verifique o caminho.")
    exit()

df = df.sort_values(by='Date')
df.set_index('Date', inplace=True)
df = df[['Close']]

# --- Cálculo de Indicadores ---
df['media_movel_4d'] = df['Close'].rolling(window=PERIODO_MEDIA_MOVEL).mean()
df.dropna(inplace=True)

# --- Início Solução 01 ---
capital = CAPITAL_INICIAL
quantidade_acoes = 0
historico_transacoes = []
portfolio_diario = []

print("--- INICIANDO SIMULAÇÃO (SOLUÇÃO 1) ---")
print(f"Capital Inicial: R$ {CAPITAL_INICIAL:.2f}\n")

# Loop principal da simulação
for i in range(DIAS_TENDENCIA, len(df)):
    
    # Preços dos últimos dias para análise de tendência
    preco_hoje = df['Close'].iloc[i]
    preco_ontem = df['Close'].iloc[i-1]
    preco_anteontem = df['Close'].iloc[i-2]
    preco_tres_dras_atras = df['Close'].iloc[i-3]
    data_hoje = df.index[i]

    tendencia_de_queda = (preco_ontem < preco_anteontem) and (preco_anteontem < preco_tres_dras_atras)
    tendencia_de_alta = (preco_ontem > preco_anteontem) and (preco_anteontem > preco_tres_dras_atras)
    
    # Lógica de Compra
    if tendencia_de_queda and capital > 0:
        acoes_a_comprar = capital / preco_hoje
        quantidade_acoes += acoes_a_comprar
        capital = 0
        transacao = {
            'Data': data_hoje.strftime('%Y-%m-%d'), 'Operação': 'COMPRA',
            'Preço (R$)': preco_hoje, 'Qtd Ações': acoes_a_comprar,
            'Capital (R$)': capital
        }
        historico_transacoes.append(transacao)
        print(f"COMPRA: {acoes_a_comprar:.4f} ações a R$ {preco_hoje:.2f} em {data_hoje.strftime('%Y-%m-%d')}")

    # Lógica de Venda
    elif tendencia_de_alta and quantidade_acoes > 0:
        capital += quantidade_acoes * preco_hoje
        acoes_vendidas = quantidade_acoes
        quantidade_acoes = 0
        transacao = {
            'Data': data_hoje.strftime('%Y-%m-%d'), 'Operação': 'VENDA',
            'Preço (R$)': preco_hoje, 'Qtd Ações': acoes_vendidas,
            'Capital (R$)': capital
        }
        historico_transacoes.append(transacao)
        print(f"VENDA: {acoes_vendidas:.4f} ações a R$ {preco_hoje:.2f} em {data_hoje.strftime('%Y-%m-%d')}")
    
    # Atualização diária do valor do portfólio
    valor_portfolio_hoje = capital + (quantidade_acoes * preco_hoje)
    portfolio_diario.append(valor_portfolio_hoje)

# --- Apresentação dos Resultados ---
print("\n--- SIMULAÇÃO FINALIZADA ---")

valor_final = capital + (quantidade_acoes * df['Close'].iloc[-1])
lucro_total = valor_final - CAPITAL_INICIAL
percentual_lucro = (lucro_total / CAPITAL_INICIAL) * 100

print("\n--- HISTÓRICO DE TRANSAÇÕES ---")
for t in historico_transacoes:
    print(f"Data: {t['Data']}, Op: {t['Operação']:<6}, Preço: {t['Preço (R$)']:>6.2f}, "
          f"Ações: {t['Qtd Ações']:>8.4f}, Capital Final: R$ {t['Capital (R$)']:>8.2f}")

print("\n--- RESULTADO FINAL ---")
print(f"Capital Inicial: R$ {CAPITAL_INICIAL:.2f}")
print(f"Valor Final do Portfólio: R$ {valor_final:.2f}")
print(f"Lucro/Prejuízo: R$ {lucro_total:.2f}")
print(f"Rentabilidade: {percentual_lucro:.2f}%")

# --- Visualização Gráfica ---
datas_compra = [pd.to_datetime(t['Data']) for t in historico_transacoes if t['Operação'] == 'COMPRA']
precos_compra = [t['Preço (R$)'] for t in historico_transacoes if t['Operação'] == 'COMPRA']
datas_venda = [pd.to_datetime(t['Data']) for t in historico_transacoes if t['Operação'] == 'VENDA']
precos_venda = [t['Preço (R$)'] for t in historico_transacoes if t['Operação'] == 'VENDA']

# Gráfico 1: Preço da Ação e Operações
plt.figure(figsize=(15, 7))
plt.plot(df.index, df['Close'], label='Preço de Fechamento (Close)', color='skyblue', alpha=0.7)
plt.plot(df.index, df['media_movel_4d'], label='Média Móvel 4 Dias', color='orange', linestyle='--')
plt.scatter(datas_compra, precos_compra, label='Pontos de Compra', marker='^', color='green', s=100, zorder=5)
plt.scatter(datas_venda, precos_venda, label='Pontos de Venda', marker='v', color='red', s=100, zorder=5)
plt.title('Simulação de Trading (Solução 1) - PETR4')
plt.xlabel('Data'); plt.ylabel('Preço (R$)'); plt.legend(); plt.grid(True)

# Gráfico 2: Evolução do Valor do Portfólio
plt.figure(figsize=(15, 5))
plt.plot(df.index[DIAS_TENDENCIA:], portfolio_diario, label='Valor do Portfólio', color='purple')
plt.axhline(y=CAPITAL_INICIAL, color='red', linestyle='--', label=f'Capital Inicial (R$ {CAPITAL_INICIAL:.2f})')
plt.title('Evolução do Valor do Portfólio ao Longo do Tempo')
plt.xlabel('Data'); plt.ylabel('Valor (R$)'); plt.legend(); plt.grid(True)

plt.show()
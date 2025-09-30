import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# --- PARÂMETROS DA SIMULAÇÃO ---
ARQUIVO_CSV = r'C:\Users\lucas\OneDrive\Documentos\Faculdade\_CADEIRAS\11 semestre\Processamento Digital de Sinais\Labs\Lab 01 - media movel\Download Data - STOCK_BR_BVMF_PETR3.csv'
CAPITAL_INICIAL = 1000.00
PERIODO_MEDIA_MOVEL = 4

# --- Carregamento e Preparação dos Dados ---
try:
    df = pd.read_csv(ARQUIVO_CSV, sep=',', parse_dates=['Date'])
except FileNotFoundError:
    print(f"ERRO: Arquivo não encontrado em '{ARQUIVO_CSV}'. Verifique o caminho.")
    exit()

df = df.sort_values(by='Date').set_index('Date')
df = df[['Close']]

# --- Geração de Sinais (Abordagem Vetorizada) ---
print("--- Gerando sinais da estratégia (sem loop)... ---")

# Cálculo do indicador
df['media_movel_4d'] = df['Close'].rolling(window=PERIODO_MEDIA_MOVEL).mean()

df['Close_ontem'] = df['Close'].shift(1)
df['media_movel_ontem'] = df['media_movel_4d'].shift(1)

# Condição de Compra: Preço cruza a média móvel para CIMA.
df['sinal_compra'] = (df['Close_ontem'] < df['media_movel_ontem']) & (df['Close'] > df['media_movel_4d'])

# Condição de Venda: Preço cruza a média móvel para BAIXO.
df['sinal_venda'] = (df['Close_ontem'] > df['media_movel_ontem']) & (df['Close'] < df['media_movel_4d'])

df.dropna(inplace=True)

# --- Motor de Simulação (Backtesting) ---
print("--- Iniciando simulação de portfólio... ---")

capital = CAPITAL_INICIAL
quantidade_acoes = 0
em_posicao = False # Flag para saber se temos ações compradas
historico_portfolio = []
historico_transacoes = []

for data, linha in df.iterrows():

    # Lógica de Compra: se o sinal for True E não tivermos ações
    if linha['sinal_compra'] and not em_posicao:
        acoes_a_comprar = capital / linha['Close']
        quantidade_acoes = acoes_a_comprar
        capital = 0
        em_posicao = True
        transacao = {'Data': data, 'Operação': 'COMPRA', 'Preço': linha['Close'], 'Qtd': acoes_a_comprar}
        historico_transacoes.append(transacao)
        print(f"COMPRA: {acoes_a_comprar:.4f} ações a R$ {linha['Close']:.2f} em {data.strftime('%Y-%m-%d')}")

    # Lógica de Venda: se o sinal for True E tivermos ações para vender
    elif linha['sinal_venda'] and em_posicao:
        capital += quantidade_acoes * linha['Close']
        acoes_vendidas = quantidade_acoes
        quantidade_acoes = 0
        em_posicao = False
        transacao = {'Data': data, 'Operação': 'VENDA', 'Preço': linha['Close'], 'Qtd': acoes_vendidas}
        historico_transacoes.append(transacao)
        print(f"VENDA: {acoes_vendidas:.4f} ações a R$ {linha['Close']:.2f} em {data.strftime('%Y-%m-%d')}")
    
    # Calcula o valor do portfólio para o dia atual e armazena
    valor_do_dia = capital + (quantidade_acoes * linha['Close'])
    historico_portfolio.append(valor_do_dia)

# Adiciona o histórico do portfólio como uma nova coluna no DataFrame
df['Portfolio'] = historico_portfolio

# --- Apresentação dos Resultados ---
print("\n--- RESULTADO FINAL ---")

valor_final = df['Portfolio'].iloc[-1]
lucro_total = valor_final - CAPITAL_INICIAL
rentabilidade = (lucro_total / CAPITAL_INICIAL) * 100

print(f"\nCapital Inicial: R$ {CAPITAL_INICIAL:,.2f}")
print(f"Valor Final do Portfólio: R$ {valor_final:,.2f}")
print(f"Lucro/Prejuízo: R$ {lucro_total:,.2f}")
print(f"Rentabilidade: {rentabilidade:.2f}%")

# --- Visualização Gráfica ---
plt.style.use('seaborn-v0_8-whitegrid')

# Gráfico 1: Preço da Ação e Operações
fig, ax1 = plt.subplots(figsize=(15, 7))
ax1.plot(df.index, df['Close'], label='Preço de Fechamento (Close)', color='skyblue', alpha=0.8)
ax1.plot(df.index, df['media_movel_4d'], label='Média Móvel 4 Dias', color='orange', linestyle='--')

# Pontos de Compra e Venda (obtidos diretamente do DataFrame)
compras = df[df['sinal_compra']]
vendas = df[df['sinal_venda']]
ax1.scatter(compras.index, compras['Close'], label='Pontos de Compra', marker='^', color='green', s=120, zorder=5)
ax1.scatter(vendas.index, vendas['Close'], label='Pontos de Venda', marker='v', color='red', s=120, zorder=5)

ax1.set_title('Simulação de Trading (Solução 02) - PETR4', fontsize=16)
ax1.set_xlabel('Data'); ax1.set_ylabel('Preço (R$)'); ax1.legend()

# Gráfico 2: Evolução do Valor do Portfólio
fig, ax2 = plt.subplots(figsize=(15, 5))
ax2.plot(df.index, df['Portfolio'], label='Valor do Portfólio', color='purple')
ax2.axhline(y=CAPITAL_INICIAL, color='red', linestyle='--', label=f'Capital Inicial (R$ {CAPITAL_INICIAL:,.2f})')
ax2.set_title('Evolução do Valor do Portfólio ao Longo do Tempo', fontsize=16)
ax2.set_xlabel('Data'); ax2.set_ylabel('Valor (R$)'); ax2.legend()

plt.tight_layout()
plt.show()
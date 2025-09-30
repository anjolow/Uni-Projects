import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

local_sinal_original = r'C:\Users\lucas\OneDrive\Documentos\Faculdade\_CADEIRAS\11 semestre\Processamento Digital de Sinais\Labs\Lab 05 - Amostragem\Sinal1 Original.csv'
local_sinal_ruidoso = r'C:\Users\lucas\OneDrive\Documentos\Faculdade\_CADEIRAS\11 semestre\Processamento Digital de Sinais\Labs\Lab 05 - Amostragem\Sinal1 Ruido.csv'

df_original = pd.read_csv(local_sinal_original, header=None)
df_ruidoso = pd.read_csv(local_sinal_ruidoso, header=None)

sinal_original = df_original.values.flatten()
sinal_ruidoso = df_ruidoso.values.flatten()

# Parâmetros iniciais
fs_original = 2400000
duracao_s = 0.1

# --- FUNÇÃO AUXILIAR PARA ANÁLISE E PLOTAGEM ---
"""
Calcula a FFT de um sinal e plota o sinal no tempo e sua FFT na frequência.   
Args:
    sinal (np.array): O vetor de dados do sinal.
    fs (int): A taxa de amostragem do sinal em Hz.
    titulo_principal (str): O título para a figura do gráfico.
    duracao_s (float): A duração total do sinal em segundos.
"""
def analisar_e_plotar(sinal, fs, titulo_principal, duracao_s):

    print(f"Analisando: {titulo_principal}...")
    
    # ---- Preparação para a FFT ----
    N = len(sinal)
    fft_complexa = np.fft.fft(sinal)
    fft_magnitude = 2/N * np.abs(fft_complexa)
    freqs = np.fft.fftfreq(N, 1/fs)
    
    # ---- Geração do Gráfico ----
    plt.figure(figsize=(12, 8))
    plt.suptitle(titulo_principal, fontsize=16)
    
    # 1. Gráfico do Sinal no Domínio do Tempo
    plt.subplot(2, 1, 1)
    tempo = np.linspace(0, duracao_s, N, endpoint=False)
    plt.plot(tempo, sinal)
    plt.title('Sinal no Domínio do Tempo')
    plt.xlabel('Tempo (s)')
    plt.ylabel('Amplitude')
    plt.grid(True)
    plt.xlim(0, 0.05)
    
    # 2. Gráfico da FFT no Domínio da Frequência
    plt.subplot(2, 1, 2)
    nyquist_limit_index = N // 2
    plt.plot(freqs[:nyquist_limit_index], fft_magnitude[:nyquist_limit_index])
    plt.title('Espectro de Frequência (FFT)')
    plt.xlabel('Frequência (Hz)')
    plt.ylabel('Magnitude')
    plt.grid(True)
    
    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    plt.show()

# --- ANÁLISE DOS SINAIS INICIAIS ---

# Plota o sinal puro
analisar_e_plotar(sinal_original, fs_original, 
                  f'Análise do Sinal Original Puro (fs = {fs_original/1e6} MHz)', duracao_s)

# Plota o sinal com o ruído
analisar_e_plotar(sinal_ruidoso, fs_original, 
                  f'Análise do Sinal com Ruído (fs = {fs_original/1e6} MHz)', duracao_s)


# --- SUBAMOSTRAGEM E ANÁLISE DOS NOVOS SINAIS ---
novas_taxas_amostragem = [600000, 300000, 100000, 48000, 16000, 9600, 2000]
sinais_ruidosos_subamostrados = {}

# Loop para subamostrar e depois analisar cada novo sinal
for nova_taxa in novas_taxas_amostragem:
    fator_passo = int(fs_original / nova_taxa) # Fator de subamostragem
    sinal_subamostrado = sinal_ruidoso[::fator_passo]
    sinais_ruidosos_subamostrados[nova_taxa] = sinal_subamostrado
    
    titulo = f'Análise do Sinal Subamostrado a {nova_taxa/1e3} kHz'
    analisar_e_plotar(sinal_subamostrado, nova_taxa, titulo, duracao_s)

print("\nAnálise completa.")


# --- CÁLCULO DO ERRO QUADRÁTICO MÉDIO (MSE) ---
print("\n--- Calculando o Erro Quadrático Médio (MSE) ---")

for nova_taxa, sinais_sub in sinais_ruidosos_subamostrados.items():
    fator_passo = int(fs_original / nova_taxa)
    
    sinal_original_sub = sinal_original[::fator_passo] # Cria versão subamostrada do sinal original para referência
    
    mse = np.mean((sinal_original_sub - sinais_sub)**2) # Cálculo de MSE em relação ao sinal original

    print(f"Taxa de Amostragem: {nova_taxa} Hz")
    print(f"  -> MSE: {mse:.9f}")
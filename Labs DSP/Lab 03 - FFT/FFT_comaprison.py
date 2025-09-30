import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

local_sinalC = r'C:\Users\lucas\OneDrive\Documentos\Faculdade\_CADEIRAS\11 semestre\Processamento Digital de Sinais\Labs\Lab 03 - FFT\sinal01_C.csv'

dfC = pd.read_csv(local_sinalC, header=None)

sinalC = dfC.values.flatten()
        
# Geração do ruído branco gaussiano
amplitude_ruido = 0.1
ruido = np.random.normal(0, amplitude_ruido, sinalC.shape)
sinalC_ruido = sinalC + ruido

fft = np.fft.fft(sinalC_ruido)

# Calculo da energia do sinal e das harmônicas
en_harmonicas = (np.abs(fft)**2)
en_sinal = np.sum(en_harmonicas)

# Indices que ordenam as energias em ordem decrescente
indices_ordenados = np.argsort(en_harmonicas)[::-1]

# Calcula a energia acumulada
en_acumulada = np.cumsum(en_harmonicas[indices_ordenados])

def filtrar_por_energia(fft, percentual):

    limiar_energia = percentual * en_sinal
    
    # Encontra quantos coeficientes são necessários para atingir o percentual de energia
    indice_corte = np.where(en_acumulada >= limiar_energia)[0][0]
    
    # Pega os índices dos coeficientes que devem ser mantidos
    indices_a_manter = indices_ordenados[:indice_corte + 1]
    
    # Cria uma máscara booleana do mesmo tamanho da FFT, inicializada com False (zerar)
    mascara = np.zeros_like(fft, dtype=bool)
    
    # Define como True as posições dos coeficientes que queremos manter
    mascara[indices_a_manter] = True
    
    # Zera os coeficientes que não estão na máscara
    fft_filtrado = fft * mascara
    
    print(f"Para {percentual*100}% de energia, mantivemos {len(indices_a_manter)} de {len(fft)} coeficientes.")
    
    return np.fft.ifft(fft_filtrado).real

# Sinais filtrados
sinalC_filtrado_93 = filtrar_por_energia(fft,0.93)
sinalC_filtrado_96 = filtrar_por_energia(fft,0.96)

# Cálculo da MSE para os sinais
mse_93 = np.mean((sinalC - sinalC_filtrado_93)**2)
mse_96 = np.mean((sinalC - sinalC_filtrado_96)**2)

print(f"Mean Square Error para 93%: {mse_93:.6f}")
print(f"Mean Square Error para 96%: {mse_96:.6f}")


# --- PLOTAGEM DOS GRÁFICOS ---

k = np.arange((len(sinalC))) # Array com N valores, começando em 0 e indo até N

# Comparação entre o sinal original e o sinal com ruido
fig, axs = plt.subplots(2, 1, figsize=(12, 12), sharex=True)

axs[0].plot(sinalC, label='Sinal Original', color='blue')
axs[0].set_title('Comparação dos Sinais')
axs[0].set_ylabel('Amplitude')
axs[0].legend()
axs[0].grid(True)

axs[1].plot(sinalC_ruido, label='Sinal com Ruído', color='red', alpha=0.8)
axs[1].set_ylabel('Amplitude')
axs[1].legend()
axs[1].grid(True)
axs[1].set_xlim(0,1000)


# Comparação entre o sinal original e os sinais reconstruídos
fig, axs = plt.subplots(2, 1, figsize=(12, 12), sharex=True)

axs[0].plot(sinalC, label='Sinal Original', color='blue')
axs[0].plot(sinalC_filtrado_93, label=f'Reconstruído (93% Energia, MSE={mse_93:.4f})', color='green')
axs[0].set_title('Comparações com sinais reconstruídos')
axs[0].set_xlabel('Amostras')
axs[0].set_ylabel('Amplitude')
axs[0].grid(True)
axs[0].legend()

axs[1].plot(sinalC, label='Sinal Original', color='blue')
axs[1].plot(sinalC_filtrado_96, label=f'Reconstruído (96% Energia, MSE={mse_96:.4f})', color='magenta')
axs[1].set_xlabel('Amostras')
axs[1].set_ylabel('Amplitude')
axs[1].grid(True)
axs[1].legend()
axs[1].set_xlim(0,1000)

plt.show()

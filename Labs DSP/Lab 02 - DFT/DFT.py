import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

local_sinal = r'C:\Users\lucas\OneDrive\Documentos\Faculdade\_CADEIRAS\11 semestre\Processamento Digital de Sinais\Labs\Lab 02 - DFT\Sinal02.csv'

df = pd.read_csv(local_sinal, header=None, names=['sinal'])

sinal = df['sinal'].to_numpy()

def DFT(x):
    N = len(x)
    X = np.zeros(N, dtype=np.complex128)

    for k in range(N):
        soma_complexa = complex(0, 0)
        for n in range(N):
            z = x[n] * np.exp(1j * (-2 * np.pi * k * n / N))
            soma_complexa += z
        X[k] = soma_complexa
    return X

def IDFT(X):
    N = len(X)
    x = np.zeros(N, dtype=np.complex128)

    for k in range(N):
        soma_complexa = complex(0, 0)
        for n in range(N):
            z = X[n] * np.exp(1j * (2 * np.pi * k * n / N))
            soma_complexa += z
        x[k] = soma_complexa
    
    return (x/N)

if __name__ == "__main__":
    dft = DFT(sinal)

    N = len(sinal) # Calcula N do sinal
    k = np.arange((N)) # Transforma o N em um array com N valores
    k1 = np.arange((N/2)) # Transforma o N em um array com N/2 valores
    freq = (2*np.pi)/N # Calcula a frequencia do sinal

    # Teste de recomposição do sinal original
    recomposto = IDFT(dft)

    # Obtém magnitude e fase do sinal após DFT
    magnitude = np.abs(dft)
    magnitude = magnitude[:len(k1)] # Limita para ver somente a parte positiva dos valores
    fase = np.angle(dft)
    fase = fase[:len(k1)] # Limita para ver somente a parte positiva dos valores
    
    # --- Rotina de Análise e Filtragem ---
    numeros_harmonicas = [3, 5, 8] # Lista dos números de harmônicas
    sinais_reconstruidos = {} # Armazena os sinais reconstruídos

    for num_harmonicas in numeros_harmonicas:
        magnitude_primeira_metade = np.abs(dft[:N // 2]) # Copia a magnitude da primeira metade do espectro para encontrar os picos
        
        indices_picos = np.argsort(magnitude_primeira_metade)[-num_harmonicas:] # Encontra os índices dos picos mais relevantes
        
        dft_filtrada = np.zeros(N, dtype=np.complex128) # Cria um array de zeros para o espectro filtrado
        
        # Copia as componentes relevantes e suas contrapartes simétricas
        for k_pico in indices_picos:
            dft_filtrada[k_pico] = dft[k_pico]
            if k_pico != 0 and k_pico != N // 2:
                dft_filtrada[N - k_pico] = dft[N - k_pico]

        # Reconstroi o sinal usando a IDFT com o espectro filtrado
        sinal_reconstruido = IDFT(dft_filtrada)
        sinais_reconstruidos[num_harmonicas] = sinal_reconstruido

    # --- Plotagem e Comparação dos Sinais ---
    fig, axs = plt.subplots(4, 1, figsize=(12, 12), sharex=True)
    
    axs[0].plot(k, sinal, label="Sinal Original")
    axs[0].set_title("Sinal Original")
    axs[0].set_ylabel("Amplitude")
    axs[0].grid(True)
    
    axs[1].plot(k, sinais_reconstruidos[3], label="3 Harmônicas")
    axs[1].set_title("Reconstruído com 3 Harmônicas Principais")
    axs[1].set_ylabel("Amplitude")
    axs[1].grid(True)
    
    axs[2].plot(k, sinais_reconstruidos[5], label="5 Harmônicas")
    axs[2].set_title("Reconstruído com 5 Harmônicas Principais")
    axs[2].set_ylabel("Amplitude")
    axs[2].grid(True)
    
    axs[3].plot(k, sinais_reconstruidos[8], label="8 Harmônicas")
    axs[3].set_title("Reconstruído com 8 Harmônicas Principais")
    axs[3].set_ylabel("Amplitude")
    axs[3].set_xlabel("Índice da Amostra (n)")
    axs[3].grid(True)
    
    # Comparação do Sinal Original e o Reconstruído com 8 Harmônicas
    plt.figure(figsize=(12, 6))
    plt.plot(k, sinal, 'k', label="Sinal Original")
    plt.plot(k, sinais_reconstruidos[8], 'r--', label="Reconstruído com 8 Harmônicas")
    plt.title("Sinal Original vs. Reconstruído (8 Harmônicas)")
    plt.xlabel("Índice da Amostra (n)")
    plt.ylabel("Amplitude")
    plt.legend()
    plt.grid(True)

    plt.show()

    # --- Plotagem do sinal original e do sinal reconstruído para provar o funcionamento do algoritmo ---
    plt.figure(figsize=(10,6))
    plt.plot(k, sinal, label="Sinal Original")
    plt.plot(k, recomposto, 'r--', label="Sinal Recomposto")
    plt.title("Gráfico do Sinal Original sobreposto pela sua Reconstrução após DFT")
    plt.xlabel("Amostras")
    plt.ylabel("Magnitude")
    plt.grid(True)

    # --- Plotagem do gráfico de Magnitude e fase do sinal após passar pela DFT
    limiar = 1e-2
    fase[magnitude < limiar] = 0

    fig, axs = plt.subplots(2, 1, figsize=(15, 8))
    # --- Gráfico da Magnitude (superior) ---
    axs[0].stem(k1, magnitude)
    axs[0].set_title("Magnitude Plot")
    axs[0].set_ylabel("|X[k]|")
    axs[0].set_xlabel("k")
    axs[0].grid(True)
    # --- Gráfico da Fase (inferior) ---
    axs[1].stem(k1, fase)
    axs[1].set_title("Phase Plot")
    axs[1].set_ylabel("angle(X[k])")
    axs[1].set_xlabel("k")
    axs[1].grid(True)

    # --- Plotagem do gráfico de Magnitude versus Frequencia
    frequencias_angular_normalizada = k1*freq
    magnitudes_metade = np.abs(dft[0:(N//2)])*2/N

    plt.figure(figsize=(10,6))
    plt.plot(frequencias_angular_normalizada, magnitudes_metade)
    plt.title("Gráfico do Sinal após DFT")
    plt.xlabel("Frequência")
    plt.ylabel("Magnitude")
    plt.grid(True)

    plt.show()

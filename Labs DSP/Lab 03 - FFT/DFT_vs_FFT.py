import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import time

local_sinalA = r'C:\Users\lucas\OneDrive\Documentos\Faculdade\_CADEIRAS\11 semestre\Processamento Digital de Sinais\Labs\Lab 03 - FFT\sinal01_A.csv'
local_sinalB = r'C:\Users\lucas\OneDrive\Documentos\Faculdade\_CADEIRAS\11 semestre\Processamento Digital de Sinais\Labs\Lab 03 - FFT\sinal01_B.csv'
local_sinalC = r'C:\Users\lucas\OneDrive\Documentos\Faculdade\_CADEIRAS\11 semestre\Processamento Digital de Sinais\Labs\Lab 03 - FFT\sinal01_C.csv'

dfA = pd.read_csv(local_sinalA, header=None)
dfB = pd.read_csv(local_sinalB, header=None)
dfC = pd.read_csv(local_sinalC, header=None)

sinalA = dfA.values.flatten()
sinalB = dfB.values.flatten()
sinalC = dfC.values.flatten()

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
    
    NA = len(sinalA)
    NB = len(sinalB)
    NC = len(sinalC)

    print("Tamanho sinal A: ", NA)
    print("Tamanho sinal B: ", NB)
    print("Tamanho sinal C: ", NC)
    
    print("-"*30)

    tempos_dft = []
    tempos_fft = []

    # --- SINAL A ---
    inicio = time.perf_counter()  # Marca o tempo de início
    DFT(sinalA)
    fim = time.perf_counter() # Marca o tempo de fim
    tempo_gasto_dft = fim - inicio
    tempos_dft.append(tempo_gasto_dft)
    print(f"  -> Tempo da DFT Sinal A: {tempo_gasto_dft:.6f} segundos")

    inicio = time.perf_counter()
    np.fft.fft(sinalA)
    fim = time.perf_counter()
    tempo_gasto_fft = fim - inicio
    tempos_fft.append(tempo_gasto_fft)
    print(f"  -> Tempo da FFT Sinal A: {tempo_gasto_fft:.6f} segundos")
    print(f"Ganho de tempo: {(tempo_gasto_dft/tempo_gasto_fft):.6f}")


    print("-"*30)


    # --- SINAL B ---
    inicio = time.perf_counter()
    DFT(sinalB)
    fim = time.perf_counter()
    tempo_gasto_dft = fim - inicio
    tempos_dft.append(tempo_gasto_dft)
    print(f"  -> Tempo da DFT Sinal B: {tempo_gasto_dft:.6f} segundos")

    inicio = time.perf_counter()
    np.fft.fft(sinalB)
    fim = time.perf_counter()
    tempo_gasto_fft = fim - inicio
    tempos_fft.append(tempo_gasto_fft)
    print(f"  -> Tempo da FFT Sinal B: {tempo_gasto_fft:.6f} segundos")
    print(f"Ganho de tempo: {(tempo_gasto_dft/tempo_gasto_fft):.6f}")
    
    print("-"*30)


    # --- SINAL C ---
    inicio = time.perf_counter()
    DFT(sinalC)
    fim = time.perf_counter()
    tempo_gasto_dft = fim - inicio
    tempos_dft.append(tempo_gasto_dft)
    print(f"  -> Tempo da DFT Sinal C: {tempo_gasto_dft:.6f} segundos")

    inicio = time.perf_counter()
    np.fft.fft(sinalC)
    fim = time.perf_counter()
    tempo_gasto_fft = fim - inicio
    tempos_fft.append(tempo_gasto_fft)
    print(f"  -> Tempo da FFT Sinal C: {tempo_gasto_fft:.6f} segundos")
    print(f"Ganho de tempo: {(tempo_gasto_dft/tempo_gasto_fft):.6f}")
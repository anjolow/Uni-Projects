import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile
from scipy.fft import dct, idct

def calculate_mse(original, reconstructed):
    return np.mean((original - reconstructed) ** 2)

def calculate_snr(original, reconstructed):
    mse = calculate_mse(original, reconstructed)
    if mse == 0:
        return float('inf')
    signal_power = np.mean(original ** 2)
    return 10 * np.log10(signal_power / mse)

def zrlc_encode(data_array):
    encoded_list = []
    zero_count = 0
    for item in data_array:
        if item == 0:
            zero_count += 1
        else:
            if zero_count > 0:
                encoded_list.append((0, zero_count))
                zero_count = 0
            encoded_list.append(item)
    if zero_count > 0:
        encoded_list.append((0, zero_count))
    return encoded_list

def zrlc_decode(encoded_list):
    decoded_list = []
    for item in encoded_list:
        if isinstance(item, tuple) and item[0] == 0:
            count = item[1]
            decoded_list.extend([0] * count)
        else:
            decoded_list.append(item)
    return np.array(decoded_list, dtype=np.int8)

# --- Carrega e trata o audio ---
fs, audio_data = wavfile.read('bom dia.wav')

# Normaliza os sinais para o intervalo [-1, 1]
tipo_dado = audio_data.dtype
audio_original = audio_data / np.iinfo(tipo_dado).max
audio_original /= np.max(np.abs(audio_original))

if audio_data.ndim > 1: audio_data = audio_data.mean(axis=1) # Verifica se o áudio é estéreo e converte para mono

# --- 2. Aplica DCT e converte para int ---
dct_coeffs = dct(audio_original, type=2)

# Encontra valor de pico para escalar
max_val = np.max(np.abs(dct_coeffs))

# Escala para o range de int8 (-127 a 127)
scaled_coeffs = (dct_coeffs / max_val) * 127.0

# Arredonda e converte para int8
quantized_coeffs = np.round(scaled_coeffs).astype(np.int8)

# --- 3. Faz a ZRLC ---
encoded_data = zrlc_encode(quantized_coeffs)
original_elements = len(quantized_coeffs)
compressed_elements = len(encoded_data)
compression_ratio = original_elements / compressed_elements

print(f"--- Implementando ZRLC ---")
print(f"Número de coeficientes original: {original_elements}")
print(f"Número de itens após ZRLC: {compressed_elements}")
print(f"Taxa de Compressão (ZRLC): {compression_ratio:.2f}x")

# --- 3. Reconstroi o sinal e calcula erros ---
decoded_coeffs_zrlc = zrlc_decode(encoded_data)
dequantized_coeffs = decoded_coeffs_zrlc.astype(np.float64) * (max_val / 127.0)
audio_reconstructed = idct(dequantized_coeffs, type=2) # Aplicar a IDCT

mse = calculate_mse(audio_original, audio_reconstructed)
snr = calculate_snr(audio_original, audio_reconstructed)

print("\n Erros:")
print(f"MSE: {mse:.8f}")
print(f"SNR: {snr:.2f} dB")

# Salva o áudio reconstruído para ouvir e comparar
audio_reconstruido_final = (audio_reconstructed * np.iinfo(tipo_dado).max).astype(tipo_dado)
caminho_saida = r'C:\Users\lucas\OneDrive\Documentos\Faculdade\_CADEIRAS\11 semestre\Processamento Digital de Sinais\Labs\Lab 07 - DCT e Janelamento\audio_reconstruido.wav'
wavfile.write(caminho_saida, fs, audio_reconstruido_final)
print(f"\nÁudio reconstruído salvo em: {caminho_saida}")


# -------------------------------------------- PLOTAGEM DOS GRÁFICOS --------------------------------------------

# Calcula o vetor de tempo para plotagem dos gráficos
N = len(audio_original)
duration = N / fs
t = np.linspace(0., duration, N)

fig, axs = plt.subplots(3, 1, figsize=(12, 8), sharex=True)

# Gráfico 1: Sinal no Domínio do Tempo (Original)
axs[0].plot(t, audio_original)
axs[0].set_title('Sinal de Áudio Original')
axs[0].set_ylabel('Amplitude')

# Gráfico 2: Sinal no Domínio do Tempo (Reconstituído)
axs[1].plot(t, audio_reconstructed)
axs[1].set_title(f'Sinal Reconstruído (SNR: {snr:.2f} dB)')
axs[1].set_ylabel('Amplitude')

# Gráfico 3: Erro linear de compressão
axs[2].plot(t, audio_original - audio_reconstructed)
axs[2].set_title('Erro de Compressão (Original - Reconstruído)')
axs[2].set_xlabel('Tempo (s)')
axs[2].set_ylabel('Amplitude do Erro')

plt.tight_layout()

# Visualização dos coeficientes DCT
plt.figure(figsize=(15, 6))
plt.subplot(1, 2, 1)
plt.plot(dct_coeffs)
plt.title('Coeficientes DCT Originais')
plt.yscale('symlog') # Escala logarítmica simétrica para ver melhor os valores pequenos
plt.ylabel('Amplitude')
plt.xlabel('Frequência')

plt.subplot(1, 2, 2)
plt.plot(dequantized_coeffs)
plt.title('Coeficientes DCT Dequantizados')
plt.yscale('symlog')
plt.ylabel('Amplitude')
plt.xlabel('Frequência')

plt.tight_layout()
plt.show()
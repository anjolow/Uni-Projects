import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile
from scipy.fft import dct, idct

def calculate_mse(original, reconstructed):
    return np.mean((original - reconstructed) ** 2)

def calculate_snr(original, reconstructed):
    mse = calculate_mse(original, reconstructed)
    if mse == 0: return float('inf')
    signal_power = np.mean(original ** 2)
    return 10 * np.log10(signal_power / mse)

# --- Funções ZRLC ---
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
            decoded_list.extend([0] * item[1])
        else:
            decoded_list.append(item)
    return np.array(decoded_list, dtype=np.int8)

# --- Carregar o mesmo áudio ---
fs, audio_data = wavfile.read('bom dia.wav')

# Normaliza os sinais para o intervalo [-1, 1]
tipo_dado = audio_data.dtype
audio_original = audio_data / np.iinfo(tipo_dado).max
audio_original /= np.max(np.abs(audio_original))

if audio_data.ndim > 1: audio_data = audio_data.mean(axis=1) # Verifica se o áudio é estéreo e converte para mono

N = len(audio_original)
duration = N / fs
t = np.linspace(0., N / fs, N)

# --- 1. Definir parâmetros dos blocos ---
block_size = 2048
overlap = 60/100
step_size = int(block_size * (1 - overlap))

# --- 2. Inicializações ---
audio_reconstructed = np.zeros_like(audio_original)
hanning_window = np.hanning(block_size)
num_blocks = (N - block_size) // step_size + 1
compression_ratios = []

# --- 3. Processamento ---
for i in range(num_blocks):
    start = i * step_size
    end = start + block_size
    
    # Extrair bloco e aplicar janela
    block = audio_original[start:end]
    windowed_block = block * hanning_window
    
    dct_coeffs_block = dct(windowed_block, type=2)
    
    # Quantização adaptativa
    max_val_block = np.max(np.abs(dct_coeffs_block))
    if max_val_block == 0: max_val_block = 1.0
    
    scaled_coeffs_block = (dct_coeffs_block / max_val_block) * 127.0
    quantized_coeffs_block = np.round(scaled_coeffs_block).astype(np.int8)
    
    # Codificação ZRLC e cálculo da compressão do bloco
    encoded_block = zrlc_encode(quantized_coeffs_block)
    compression_ratios.append(len(quantized_coeffs_block) / len(encoded_block))
    
    # Decodificação ZRLC e Dequantização
    decoded_coeffs_zrlc_block = zrlc_decode(encoded_block)
    dequantized_coeffs_block = decoded_coeffs_zrlc_block.astype(np.float64) * (max_val_block / 127.0)
    
    # IDCT
    reconstructed_block_idct = idct(dequantized_coeffs_block, type=2)
    
    # Aplicar janela novamente e somar com sobreposição
    audio_reconstructed[start:end] += reconstructed_block_idct * hanning_window

mse = calculate_mse(audio_original, audio_reconstructed)
snr = calculate_snr(audio_original, audio_reconstructed)

print(f"\nTaxa de Compressão Média (ZRLC): {np.mean(compression_ratios):.2f}x")
print(f"MSE: {mse:.8f}")
print(f"SNR: {snr:.2f} dB")

# Salva o áudio reconstruído para ouvir e comparar
audio_reconstruido_final = (audio_reconstructed * np.iinfo(tipo_dado).max).astype(tipo_dado)
caminho_saida = r'C:\Users\lucas\OneDrive\Documentos\Faculdade\_CADEIRAS\11 semestre\Processamento Digital de Sinais\Labs\Lab 07 - DCT e Janelamento\audio_reconstruido2.wav'
wavfile.write(caminho_saida, fs, audio_reconstruido_final)
print(f"\nÁudio reconstruído salvo em: {caminho_saida}")

# -------------------------------------------- PLOTAGEM DOS GRÁFICOS --------------------------------------------

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
plt.show()
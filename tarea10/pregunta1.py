import random
import math
import cmath
from fractions import Fraction

def dft_amplitudes(state_vector):
    """
    Calcula la Transformada Discreta de Fourier (DFT) de un vector de estado.
    """
    N = len(state_vector)
    output = []

    # Se optimiza calculando solo sobre los índices no nulos del estado disperso.
    non_zero_indices = [i for i, amp in enumerate(state_vector) if abs(amp) > 0]
    
    for k in range(N):
        sum_val = 0j
        for x in non_zero_indices:
            # Fórmula de la QFT: sum(x_j * exp(2*pi*i * j * k / N))
            # Normalización habitual es 1/sqrt(N) aplicada en la transformación
            angle = 2 * math.pi * x * k / N
            sum_val += state_vector[x] * cmath.exp(1j * angle)
        output.append(sum_val / math.sqrt(N))
    return output

def get_factors_from_period(N, a, r):
    """
    Intenta obtener factores usando el periodo r.
    """
    if r % 2 != 0:
        return None  # El periodo debe ser par
    
    val = pow(a, r // 2, N)
    if val == N - 1:
        return None  # Caso trivial a^(r/2) = -1 mod N
    
    f1 = math.gcd(val - 1, N)
    f2 = math.gcd(val + 1, N)
    return f1, f2

def simulate_shor(N=35):
    print(f"--- Simulando Algoritmo de Shor para N={N} ---")
    
    # Configuración de registros
    # Q debe ser una potencia de 2 tal que Q >= N^2. 
    # 35^2 = 1225, así que se usa Q = 2048 (2^11).
    Q = 2048
    print(f"Tamaño del registro cuántico (Q): {Q}")
    
    max_attempts = 10
    
    for attempt in range(1, max_attempts + 1):
        print(f"\nIntento #{attempt}")
        
        # Elegir a aleatorio
        a = random.randint(2, N - 1)
        print(f"  Valor elegido 'a': {a}")
        
        # Chequeo clásico inicial (GCD)
        g = math.gcd(a, N)
        if g > 1:
            print(f"  ¡Éxito temprano! El valor elegido comparte factor con N.")
            print(f"  Factor encontrado: {g}")
            return
        
        # Simulación Cuántica
        print("  -> Simulando registros y f(x) = a^x mod N...")
        
        # Se simula el medir el segundo registro.
        # Primero, se elige un 'x_seed' aleatorio para determinar qué valor 'z' colapsa.
        x_seed = random.randint(0, Q - 1)
        observed_z = pow(a, x_seed, N)
        
        # Se identifican todos los estados |x> compatibles con este z
        collapsed_indices = [x for x in range(Q) if pow(a, x, N) == observed_z]
        print(f"  -> 2do registro medido: {observed_z}. 1er registro colapsa a {len(collapsed_indices)} estados.")
        
        # Creamos el vector de estado (amplitudes)
        # Estado es una superposición uniforme sobre los índices encontrados
        state = [0j] * Q
        amplitude = 1.0 / math.sqrt(len(collapsed_indices))
        for idx in collapsed_indices:
            state[idx] = amplitude
            
        # Aplicar QFT (usando DFT clásica)
        print("  -> Calculando amplitudes de QFT (vía DFT)...")
        transformed_state = dft_amplitudes(state)
        
        # Se calculan probabilidades |amp|^2
        probabilities = [abs(val)**2 for val in transformed_state]
        
        # Medición del 1er registro
        # Se elige un índice 'y' basado en las probabilidades
        measured_y = random.choices(range(Q), weights=probabilities, k=1)[0]
        prob_measured = probabilities[measured_y]
        print(f"  -> Valor medido y: {measured_y} (Probabilidad: {prob_measured:.4f})")
        
        if measured_y == 0:
            print("  -> Medición 0 no da información. Reintentando.")
            continue

        # Fracciones Continuas para hallar el periodo r
        # Se aproxima y/Q ≈ k/r
        try:
            # limit_denominator(N) busca la fracción más cercana con denom < N
            frac = Fraction(measured_y, Q).limit_denominator(N)
            r_candidate = frac.denominator
            print(f"  -> Fracción aproximada de {measured_y}/{Q} es {frac.numerator}/{frac.denominator}")
            print(f"  -> Posible periodo r: {r_candidate}")
            
            # Se verifica si es el periodo verdadero
            if pow(a, r_candidate, N) == 1:
                print(f"  -> ¡Periodo r={r_candidate} confirmado!")
                
                factors = get_factors_from_period(N, a, r_candidate)
                if factors:
                    f1, f2 = factors
                    if f1 not in [1, N] or f2 not in [1, N]:
                        print(f"\n¡ÉXITO! Factores encontrados no triviales.")
                        print(f"Factores de {N}: {f1} y {f2}")
                        return
                    else:
                        print("  -> Factores triviales encontrados. Reintentando.")
                else:
                    print("  -> El periodo es impar o caso trivial fallido. Reintentando.")
            else:
                print(f"  -> r={r_candidate} no es el periodo (a^r = {pow(a, r_candidate, N)} mod N).")
                
        except Exception as e:
            print(f"Error en cálculo de fracciones: {e}")

    print("\nSe alcanzaron los 10 intentos sin éxito.")

# Ejecutar la simulación
if __name__ == "__main__":
    simulate_shor(35)
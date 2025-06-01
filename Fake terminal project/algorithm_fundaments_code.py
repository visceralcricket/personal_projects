"""---------------------------------------------------------------------------

Navegantes Estelares: La Ruta del Cristal Cósmico

Propósito: Leer nombre de cada cadete y su n° posicional, la cantidad de
fragmentos recolectados y el valor de cada uno; mostrar la cantidad total de
fragmentos y la suma de sus valores, el valor más bajo, el promedio truncado y
determinar si el cadete es capaz de activar el cristal cósmico o no.
Finalizar programa al recibir el nombre 'FIN' y sí y solo sí hay más de 1 cadete,
mostrar porcentaje de cadetes que SI y NO activaron el cristal cósmico redondeado
a 2 decimales.

    
Parámetros: Nombre cadete, n° posición, cantidad fragmentos recolectados y valor
de cada uno.

Variables: propiedades 1, 2, 3 y 4 respectivamente (prop_1, prop_2, prop_3, prop_4),
suma_divisores, pudo_activar_cristal, main(contiene el programa principal).


Retorna: N° del cadete en análisis, la cantidad de fragmentos recolectados, la suma
de los valores de cada fragmento, el valor mínimo de los mismos, el promedio trun-
cado del valor total (suma),¿ y si fue o no capaz de activar el cristal.
Finaliza con un reporte final que incluye el total de cadetes procesados y el
porcentaje de cadetes que SÍ y NO pudieron activar el cristal cósmico
    

----------------------------------------------------------------------------"""
    
# Función : evaluar si x (int) == a la suma de dos valores consecutivos (bool)
def prop_1(x):
    a = 1
    while a + (a + 1) <= x:
        if x == a + (a + 1):
            return True
        a += 1
    return False
"""-------------------------------------------------------------------------
Función:
facilitar la evaluación de la propiedad 2, es decir, si la suma total de los
valores de los fragmentos es o no un número deficiente (la suma de sus divisores
exceptuando al mismo número es menor al mismo).
----------------------------------------------------------------------------"""
def suma_divisores(n) :
    if n == 1 :
        return 0
    # n > 1
    suma = 1
    if n % 2 == 0 :
        inicio = 2
        fin = n // 2
        for divisor in range(inicio, fin + 1) :
            if n % divisor == 0 :
                suma += divisor
        return suma
        
    else :
        inicio = 3
        fin = n // 3
        for divisor in range(inicio, fin + 1, 2) :
            if n % divisor == 0 :
                suma += divisor
            
        return suma

# Función: evaluar si la propiedad 2 se cumple o no mediante suma_divisores
def prop_2(n) :
    return suma_divisores(n) < n

"""------------------------------------------------------------------------
Función:
evaluar si el valor mínimo de los fragmentos recolectados es o no
un número triangular------------------------------------------------------"""
def prop_3(m):
    i = 1
    while i * (i + 1) // 2 <= m:
        if i * (i + 1) // 2 == m:
            return True
            
        i += 1
    return False

"""------------------------------------------------------------------
Función:
Determinar si el valor truncado del promedio incluye al menos una vez
al dígito 2
---------------------------------------------------------------------"""
def prop_4(average):
    while average > 0:
        digito = average % 10
        if digito == 2:
            return True
        average //= 10
    return False
    
"""----------------------------------------------------------------------
Función:
Establecer un intermediario que permita conectar los argumentos
(cantidad de fragmentos, suma, valor mínimo, promedio) con las funciones
establecidas para la evaluación de las propiedades
-------------------------------------------------------------------------"""
def pudo_activar_cristal(cond1, cond2, cond3, cond4):
    return prop_1(cond1) and prop_2(cond2) and prop_3(cond3) and prop_4(cond4)

# Función: contener el programa principal y ejecutarlo al ser llamado
def main():
    
    # Inicializar variables
    activaron_crist = 0
    no_activaron_crist = 0
    num_cadetes = 0
    
    # ======= LECTURA DE DATOS DEL CADETE EN CICLO CONTROLADO ======
    
    while True:
        nombre = input()
        
        # Finalizar el programa <=> el valor de entrada == 'FIN'
        if nombre == 'FIN':
            break # Romper el ciclo para no calcular estadísticas ni leer valores
        
        num_cadetes += 1 # Aumentar en 1 el contador en caso contrario
        
        cant_frag = int(input()) # Leer la cantidad de fragmentos a contar
        
        suma = 0 # Inicalizar la suma total de sus valores
        
        valor_min = 9999 # Inicalizar valor mínimo que pueda ser actualizado
        
        for i in range(1, cant_frag + 1): # Cuenta de 1 en 1 hasta cant_fragmentos
        
            valor_frag = int(input()) # Leer cada valor de los fragmentos
            
            if valor_frag < valor_min: # Actualizar valor mínimo de ser verdadero
                valor_min = valor_frag
            suma += valor_frag
            
        # Calcular el promedio de los valores de los fragmentos
        promedio = suma // cant_frag
        
        # Imprimir la información correspondiente a cada cadete
        print(f"""CADETE #{num_cadetes} --> {nombre}
TOTAL FRAGMENTOS RECOLECTADOS = {cant_frag}
SUMA VALORES DE FRAGMENTOS RECOLECTADOS = {suma}
MENOR VALOR FRAGMENTOS RECOLECTADOS = {valor_min}
PROMEDIO TRUNCADO VALORES FRAGMENTOS RECOLECTADOS = {promedio}""")
        
        # Determinar si pudo activar el cristal o no y llevar contadores en
        # ambos casos
        if pudo_activar_cristal(cant_frag, suma, valor_min, promedio):
            print("SI PUEDE ACTIVAR EL CRISTAL CÓSMICO")
            activaron_crist += 1
            
        else:
            print("NO PUEDE ACTIVAR EL CRISTAL CÓSMICO")
            no_activaron_crist += 1
            
        # Imprimir separador de casos después de cada cadete analizado
        print("----------------------------------------------------------------")
        
        # Imprimir reporte final / caso predeterminado para n° cadetes == 0
    print("REPORTE FINAL")
    print("=============")
    print(f"TOTAL DE CADETES PROCESADOS : {num_cadetes}")
            
    # Realizar cálculo de porcentajes <=> se procesaron más de 0 cadetes
    if num_cadetes > 0:
        porcent_activaron = round((activaron_crist * 100) / num_cadetes, 2)
        porcent_no_activaron = round((no_activaron_crist * 100) / num_cadetes, 2)
        print(f"% CADETES QUE ACTIVARON CRISTAL CÓSMICO = {porcent_activaron}")
        print(f"% CADETES QUE NO ACTIVARON CRISTAL CÓSMICO = {porcent_no_activaron}")
        
# Llamar al programa principal para que este inicie
main()

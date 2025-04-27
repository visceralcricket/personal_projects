# ==== MAIN ====

def mult(x, y):
    return x * y

def div(x, y):
    return x / y

def add(x, y):
    return x + y

def subst(x, y):
    return x - y

def elevar(x, y):
    return pow(x, y)

def rest(x, y):
    return x % y

# ==== SECONDARY ====

def val_ab(x):
    if x < 0:
        return x * -1
    return x

def fact(x):
    if x <= 1:
        return 1
    acc_val = 1
    for i in range(1, x + 1):
        acc_val *= i
    return acc_val

# ==== HELPERS ====

def get_two_val():
    x = int(input("Ingrese el primer valor: "))
    y = int(input("Ingrese el segundo valor: "))
    return x, y

def get_one_val():
    x = int(input("Ingrese el valor: "))
    return x

# Diccionario de valores con sus respectivas funciones
operations = {
    1: add,
    2: subst,
    3: mult,
    4: div,
    5: elevar,
    6: rest,
    7: fact,
    8: val_ab
}

two_args= {1, 2, 3, 4, 5, 6}
one_arg = {7, 8}


while True:

    # Utilizar funcion 'try' para crear un caso donde el valor de entrada si es valido:
    try:
        # Leer respuesta del usuario y entrar en ciclo hasta que el usuario decida salir
        response = int(input("""Ingrese la operacion que desea realizar :
            1) Sumar
            2) Restar
            3) Multiplicar
            4) Dividir
            5) Elevar
            6) Resto
            7) Factorial
            8) Valor Absoluto
> """))
        
        # Verificamos si la operacion ingresada es valida

        if response not in operations: # Detectamos si hubo una inconcordancia entre el valor de entrada y los valores admitidos
            raise ValueError # Forzamos una excepción ValueError para que el programa actúe de forma específica en caso de que salte un error
        
    except ValueError: # Determinamos que ocurre si se llega a un error/existe un ValueError
        print("Entrada inválida! Por favor ingrese un numero de operación válido.")
        continue    


    try:

        if response in two_args: # Preguntar para los casos en que el usuario necesita ingresar 2 valores
            x, y = get_two_val()
            if response == 4 and y == 0: # Manejar caso en que se indique que la division es x / 0 (no valido)
                print("La división con denominador 0 no es válida!")
                continue # Saltar el ciclo que le sigue en ejecución (except ValueError) e ingresar directamente a la verificación if validation == 1 :
            result = operations[response](x, y)

        else:
            x = get_one_val()
            result = operations[response](x)

    except ValueError: # Casos en que el valor de entrada no sea valido
        print("Entrada inválida! Asegúrese de ingresar uno de los numeros presentados.")
        continue # Salta el ciclo hasta la lectura de la variable leave_comm para determinar si el usuario reintentará o no


    print(f"Resultado = {result}")
        
    leave_comm = input("Presione 0 para salir o continúe con otra operación!")
        
    if leave_comm == '0': # Preguntamos por 0 en formato str ya que lo leímos como input() y esta funcion automaticamente lo retorna como str y no int
        break

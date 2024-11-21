import numpy as np
import matplotlib.pyplot as plt

k = 8.9875517923e9  

def polar_to_cartesian(r, theta):
    """
    Преобразование из полярной системы в декартову.
    """
    x = r * np.cos(np.radians(theta))
    y = r * np.sin(np.radians(theta))
    return x, y

def parse_charge_input(input_str):
    """
    Преобразует ввод пользователя, поддерживая формат 10^x для зарядов.
    """
    components = input_str.split()
    if len(components) == 3:
        x, y_or_r, q = components
        q = q.replace("^", "**")  
        return float(x), float(y_or_r), eval(q)  
    raise ValueError

def get_user_input():
    charges = []
    print("Введите параметры зарядов. Выберите систему координат:")
    print("1: Декартовая (x, y, q) — x, y в метрах, q в кулонах (можно вводить как 1e-9 или 1*10^-9)")
    print("2: Полярная (r, θ, q) — r в метрах, θ в градусах, q в кулонах (можно вводить как 1e-9 или 1*10^-9)")

    coord_system = input("Выберите систему (1 или 2): ")
    if coord_system not in ("1", "2"):
        print("Ошибка: выбран неверный вариант. По умолчанию будет использована Декартова система.")
        coord_system = "1"

    if coord_system == "1":
        print("Вы выбрали Декартовую систему. Вводите x, y (в метрах) и q (в кулонах), например:")
        print("0 0 1*10^-9 (заряд в центре)")
        print("1 1 -1*10^-9 (заряд в точке (1, 1))")
    else:
        print("Вы выбрали Полярную систему. Вводите r, θ (в метрах и градусах) и q (в кулонах), например:")
        print("1 0 1*10^-9 (заряд на расстоянии 1 м под углом 0°)")
        print("1 180 -1*10^-9 (заряд на расстоянии 1 м под углом 180°)")

    print("Для завершения ввода оставьте строку пустой и нажмите Enter.")

    while True:
        if coord_system == "1":
            input_str = input("Введите x, y и q (через пробел): ")
        else:
            input_str = input("Введите r, θ и q (через пробел): ")

        if not input_str.strip():
            break
        try:
            if coord_system == "1":
                x, y, q = parse_charge_input(input_str)
            else:
                r, theta, q = parse_charge_input(input_str)
                x, y = polar_to_cartesian(r, theta)

            charges.append((x, y, q))
        except Exception:
            print("Ошибка: введите корректные данные в формате x y q или r θ q, где q можно вводить как 1*10^-9.")

    return charges

def plot_electric_field(charges):
    x = np.linspace(-5, 5, 200)
    y = np.linspace(-5, 5, 200)
    X, Y = np.meshgrid(x, y)

    Ex = np.zeros(X.shape)
    Ey = np.zeros(Y.shape)

    for (x0, y0, q) in charges:
        dx = X - x0
        dy = Y - y0
        r_squared = dx**2 + dy**2
        r_squared[r_squared == 0] = 1e-12 
        r = np.sqrt(r_squared)
        
        Ex += k * q * dx / r_squared
        Ey += k * q * dy / r_squared

    magnitude = np.sqrt(Ex**2 + Ey**2)
    Ex_norm = Ex / magnitude
    Ey_norm = Ey / magnitude

    plt.figure(figsize=(8, 6))

    plt.streamplot(X, Y, Ex, Ey, color=magnitude, cmap='viridis', linewidth=1.5)

    for (x0, y0, q) in charges:
        if q > 0:
            plt.plot(x0, y0, 'ro', markersize=10)  
        else:
            plt.plot(x0, y0, 'bo', markersize=10) 

    plt.title("Электростатическое поле точечных зарядов")
    plt.xlabel("x, м")
    plt.ylabel("y, м")
    plt.colorbar(label="Напряженность поля")
    plt.axis('equal')
    plt.grid()
    plt.show()

charges = get_user_input()

if charges:
    plot_electric_field(charges)
else:
    print("Не было введено ни одного заряда.")

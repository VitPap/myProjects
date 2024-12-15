import numpy as np
import matplotlib.pyplot as plt

print("Введите данные для зарядов. Ограничения:")
print("  - Величина заряда (в Кл): любое число (например, 1, -1, 0.5 и т.д.)")
print("  - Координаты (x, y): значения в пределах от -5 до 5")

num_charges = int(input("Введите количество зарядов (целое число): "))
charges = []
for i in range(num_charges):
    print(f"Введите данные для заряда {i+1}:")
    q = float(input("  Величина заряда (в Кл): "))
    
    while True:
        x = float(input("  x-координата (от -5 до 5): "))
        y = float(input("  y-координата (от -5 до 5): "))
        if -5 <= x <= 5 and -5 <= y <= 5:
            break
        else:
            print("  Ошибка: координаты должны быть в пределах от -5 до 5. Повторите ввод.")
    
    charges.append({"q": q, "pos": (x, y)})

x = np.linspace(-5, 5, 500)
y = np.linspace(-5, 5, 500)
X, Y = np.meshgrid(x, y)

Ex, Ey = np.zeros_like(X), np.zeros_like(Y)
phi = np.zeros_like(X)

for charge in charges:
    q = charge["q"]
    pos = charge["pos"]
    rx = X - pos[0]
    ry = Y - pos[1]
    r = np.sqrt(rx**2 + ry**2)
    r[r == 0] = 1e-12
    Ex += q * rx / r**3
    Ey += q * ry / r**3
    phi += q / r

print("\nДобавление диполя в систему:")
dipole_x = float(input("  x-координата диполя (от -5 до 5): "))
dipole_y = float(input("  y-координата диполя (от -5 до 5): "))
dipole_magnitude = float(input("  Модуль дипольного момента (в Кл*м): "))
dipole_angle = float(input("  Угол диполя относительно оси x (в градусах): "))

p_x = dipole_magnitude * np.cos(np.radians(dipole_angle))
p_y = dipole_magnitude * np.sin(np.radians(dipole_angle))

Ex_dipole = Ex[np.abs(Y[:, 0] - dipole_y).argmin(), np.abs(X[0, :] - dipole_x).argmin()]
Ey_dipole = Ey[np.abs(Y[:, 0] - dipole_y).argmin(), np.abs(X[0, :] - dipole_x).argmin()]

F_x = p_x * Ex_dipole
F_y = p_y * Ey_dipole

M_z = p_x * Ey_dipole - p_y * Ex_dipole

print("\nРезультаты расчета:")
print(f"  Сила, действующая на диполь: F_x = {F_x:.2e} Н, F_y = {F_y:.2e} Н")
print(f"  Момент силы относительно оси z: M_z = {M_z:.2e} Н*м")

plt.figure(figsize=(8, 8))
plt.streamplot(X, Y, Ex, Ey, color='blue', linewidth=1, density=1.5)
contours = plt.contour(X, Y, phi, levels=20, colors='red')
plt.clabel(contours, inline=True, fontsize=8)
plt.scatter([charge["pos"][0] for charge in charges],
            [charge["pos"][1] for charge in charges],
            c='black', s=50, zorder=5, label='Точечные заряды')
plt.quiver(dipole_x, dipole_y, p_x, p_y, color='green', scale=5, label='Диполь')
plt.xlim(-5, 5)
plt.ylim(-5, 5)
plt.gca().set_aspect('equal')
plt.title("Линии напряженности и эквипотенциальные поверхности")
plt.legend()
plt.show()

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def get_float_input(prompt, min_value=None, max_value=None):
    while True:
        try:
            value = float(input(prompt))
            if (min_value is not None and value < min_value) or (max_value is not None and value > max_value):
                print(f"Введите значение в диапазоне от {min_value} до {max_value}.")
            else:
                return value
        except ValueError:
            print("Введите корректное число.")

mass = get_float_input("Введите массу груза (кг): ", min_value=0.01)
k = get_float_input("Введите коэффициент жесткости пружины (Н/м): ", min_value=0.01)
c = get_float_input("Введите коэффициент сопротивления среды (кг/с): ", min_value=0.0)
v0 = get_float_input("Введите начальную скорость (м/с): ")

dt = 0.01
t_max = 20
x0 = 1.0

time = np.arange(0, t_max, dt)
x = x0
v = v0
kinetic_energy = []
potential_energy = []
total_energy = []

for t in time:
    force_spring = -k * x
    force_damping = -c * v
    acceleration = (force_spring + force_damping) / mass
    ke = 0.5 * mass * v**2
    pe = 0.5 * k * x**2
    te = ke + pe
    kinetic_energy.append(ke)
    potential_energy.append(pe)
    total_energy.append(te)
    v += acceleration * dt
    x += v * dt

fig, ax = plt.subplots(figsize=(10, 6))
ax.set_xlim(0, t_max)
ax.set_ylim(0, max(max(kinetic_energy), max(potential_energy), max(total_energy)) * 1.1)
ax.set_xlabel('Время (с)')
ax.set_ylabel('Энергия (Дж)')
ax.set_title('Энергетические превращения при колебании груза на пружине')
ax.grid()

line_ke, = ax.plot([], [], label='Кинетическая энергия (J)', color='orange')
line_pe, = ax.plot([], [], label='Потенциальная энергия (J)', color='purple')
line_te, = ax.plot([], [], label='Полная механическая энергия (J)', color='cyan')
ax.legend()

def init():
    line_ke.set_data([], [])
    line_pe.set_data([], [])
    line_te.set_data([], [])
    return line_ke, line_pe, line_te

def update(frame):
    t = time[:frame]
    line_ke.set_data(t, kinetic_energy[:frame])
    line_pe.set_data(t, potential_energy[:frame])
    line_te.set_data(t, total_energy[:frame])
    return line_ke, line_pe, line_te

ani = animation.FuncAnimation(fig, update, frames=len(time), init_func=init, blit=True, interval=10)
plt.show()
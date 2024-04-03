import matplotlib.pyplot as plt
import numpy as np


def f(x, y):
    return x**3 + y**2 - x*y - 2*x + 3*y - 4

def main():
  x_vals = np.loadtxt('bin/x_vals_method1.txt')
  y_vals = np.loadtxt('bin/y_vals_method1.txt')
  z_vals = f(x_vals, y_vals)

  X = np.linspace(x_vals.min() - 1, x_vals.max() + 1, 400)
  Y = np.linspace(y_vals.min() - 1, y_vals.max() + 1, 400)
  X, Y = np.meshgrid(X, Y)
  Z = f(X, Y)

  fig = plt.figure()
  ax = fig.add_subplot(111, projection='3d')

  traj = ax.plot(x_vals, y_vals, z_vals, color='r', label='Траектория спуска', alpha=1, marker='o', markersize=3)
  surf = ax.plot_surface(X, Y, Z, cmap='viridis', alpha=0.6, edgecolor='none')

  ax.legend()
  ax.set_xlabel('Ось X')
  ax.set_ylabel('Ось Y')
  ax.set_zlabel('f(X, Y)')
  plt.title('Градиентный спуск по f(x, y)')
  plt.savefig('img/method1.png')

if __name__ == '__main__':
  main()
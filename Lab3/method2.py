import numpy as np
import matplotlib.pyplot as plt

def f(x1, x2):
    return x1**3 + x2**2 - x1*x2 - 2*x1 + 3*x2 - 4

def main():
  x_cord = np.loadtxt('bin/x_vals_method2.txt')
  y_cord = np.loadtxt('bin/y_vals_method2.txt')
  z_cord = np.loadtxt('bin/z_vals_method2.txt')

  x1 = np.linspace(min(x_cord)-1, max(x_cord)+1, 400)
  x2 = np.linspace(min(y_cord)-1, max(y_cord)+1, 400)
  X1, X2 = np.meshgrid(x1, x2)
  Z = f(X1, X2)

  fig = plt.figure()
  ax = fig.add_subplot(111, projection='3d')
  ax.view_init(elev=20, azim=-35)

  traj = ax.plot(x_cord, y_cord, z_cord, color='r', label='Траектория', alpha=1, marker='o', markersize=3)
  surf = ax.plot_surface(X1, X2, Z, cmap='viridis', alpha=0.6, edgecolor='none')

  ax.set_title('Визуализация овражного метода')
  ax.set_xlabel('X1')
  ax.set_ylabel('X2')
  ax.set_zlabel('f(X1, X2)')
  ax.legend()
  plt.savefig('img/method2.png')

if __name__ == '__main__':
    main()
#include <iostream>
#include <limits>

int main() {
  // target area: x=277..318, y=-92..-53
  int x_min = 277;
  int x_max = 318;
  int y_min = -92;
  int y_max = -53;

  auto ypos_func = [](int steps, int y_start) { return steps * y_start - steps * (steps - 1) / 2; };

  int vy_max = -y_min - 1;
  int steps = vy_max + 1;
  int max_y = ypos_func(steps, vy_max);
  std::cout << "Reached maximum y position " << max_y << "\n";

  auto reaches = [x_min, x_max, y_min, y_max](int vx, int vy) {
    int posx = 0, posy = 0;
    while (true) {
      posx += vx;
      posy += vy;
      if (posx >= x_min && posx <= x_max && posy >= y_min && posy <= y_max)
        return true;
      vy--;
      if (vx > 0)
        vx--;
      if (posy < y_min)
        break;
      if (posx > x_max)
        break;
      if (vx == 0 && posx < x_min)
        break;
    }
    return false;
  };

  unsigned cnt = 0;
  for (int vy = y_min; vy <= vy_max; vy++) {
    for (int vx = 1; vx <= x_max; vx++) {
      if (reaches(vx, vy))
        cnt++;
    }
  }
  std::cout << "Counted " << cnt << " number of unique velocities.\n";
}
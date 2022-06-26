#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "lal.h"
const int size_pixel = 32; // размер одной клетки массива
const int field_for_x = 40, field_for_y = 30; // размерность массива
int snakex = field_for_x / 2; // изначальная позиция змейки по Х
int snakey = field_for_y / 2; // изначальная позиция змейки по Y
int snakelength = 4;  // изначальная длина змейки
int flag = 0; // флаг окочания игры

std::string basedirection = "down"; // изначальное направление змейки

std::vector<std::vector<int>> mainfield(field_for_y, std::vector<int>(field_for_x)); // вектор значения поля

/*
 * Заполнение массива mainfield нулями
 */

bool zero_vector() {
   int t = 0;
   for (int i = 0; i < field_for_y; i++)
      for (int j = 0; j < field_for_x; j++)
      {
         mainfield[i][j] = 0;
         t++;
      }
   if (t==field_for_x*field_for_y)
      return true;
   else
      return false;
}

/*
 * Изначальное добавление змейки в игру
 * snakey - координата змейкм по оси oY
 */

void snake_pos() {
   for (int i = 0; i < snakelength; i++) {
      snakey++;
      mainfield[snakey][snakex] = i + 1;
   }
}

/*
 *Функция, проверяющая пустые клетки (без змейки) и спавн яблока
 * а - массив отображения пустых/заполненных клеток
 * cnt - счетчик пустых клеток, позже нужная пустая клетка
 * temp - переменная (счетчик) проверки попали мы в нужную клетку или еще нет
 * x, y - координаты нужной клетки
 * return функции - координаты клетки
 */

std::pair<int, int> check_free_space_and_spawn_apple() {
   int a[field_for_y][field_for_x];
   int cnt = 0;
   for (int i = 0; i < field_for_y; i++) {
      for (int j = 0; j < field_for_x; j++) {
         if (mainfield[i][j] == 0) {
            cnt++;
            a[i][j] = 0;
         } else
            a[i][j] = 1;
      }
   }
   srand((unsigned) time(0));
   cnt = 1 + rand() % cnt;
   int temp = 0, x, y;
   for (int i = 0; i < field_for_y; i++) {
      for (int j = 0; j < field_for_x; j++) {
         if (a[i][j] == 0) {
            temp++;
            if (temp == cnt) {
               x = j;
               y = i;
               break;
            }
         }
      }
   }
   return std::make_pair(x, y);
}

/*
 * вызов функции проверки и спавна яблока
 * на место спавна яблока пишем значение -1
 */

void creating_apple() {
   std::pair<int, int> apple = check_free_space_and_spawn_apple();
   mainfield[apple.second][apple.first] = -1;

}

/*
 * окончание игры
 */

void game_over() {
   flag = 1;
}

/*
 * проверка хода змейки
 * если съедает яблоко -> спавн нового, увеличение змейки
 * если попадает на клетку со змейкой -> вызов окончания игры
 */

void checking_pos() {
   if (mainfield[snakey][snakex] == 0) {
   } else if (mainfield[snakey][snakex] == -1) {
      snakelength++;
      creating_apple();
   } else {
      game_over();
   }
}

/*
 * изменение координаты змейки
 * позже вызов функции проверки, куда попала змейка
 */

void change_coor() {
   if (basedirection == "up") {
      snakey--;
      if (snakey == -1)
         snakey = field_for_y - 1;
   } else if (basedirection == "down") {
      snakey++;
      if (snakey == field_for_y)
         snakey = 0;
   } else if (basedirection == "left") {
      snakex--;
      if (snakex == -1)
         snakex = field_for_x - 1;
   } else {
      snakex++;
      if (snakex == field_for_x)
         snakex = 0;
   }
   checking_pos();
}

/*
 * сам непосредственно ход змейки, где изменяются значения массива
 */

void making_move() {
   mainfield[snakey][snakex] = snakelength + 1;
   for (int i = 0; i < field_for_y; i++) {
      for (int j = 0; j < field_for_x; j++) {
         if (mainfield[i][j] > 0) {
            mainfield[i][j]--;
         }
      }
   }
}

/*
 * вызов перемещения змейки
 */

void moving_snake() {
   change_coor();
   making_move();
}

/*
 * отрисовка изображений и различных картинок для игры
 * ma - значение в массиве головы змейки
 */

void draw_area(sf::RenderWindow &window) {
   sf::Texture base_image1;
   base_image1.loadFromFile("images/field_1.png");
   sf::Sprite based1;
   based1.setTexture(base_image1);

   sf::Texture base_image2;
   base_image2.loadFromFile("images/field_2.png");
   sf::Sprite based2;
   based2.setTexture(base_image2);

   sf::Texture snake_image;
   snake_image.loadFromFile("images/snake.png");
   sf::Sprite snake;
   snake.setTexture(snake_image);

   sf::Texture snake_head_image_up;
   snake_head_image_up.loadFromFile("images/headu.png");
   sf::Sprite snake_head_up;
   snake_head_up.setTexture(snake_head_image_up);

   sf::Texture snake_head_image_down;
   snake_head_image_down.loadFromFile("images/headd.png");
   sf::Sprite snake_head_down;
   snake_head_down.setTexture(snake_head_image_down);

   sf::Texture snake_head_image_left;
   snake_head_image_left.loadFromFile("images/headl.png");
   sf::Sprite snake_head_left;
   snake_head_left.setTexture(snake_head_image_left);

   sf::Texture snake_head_image_right;
   snake_head_image_right.loadFromFile("images/headr.png");
   sf::Sprite snake_head_right;
   snake_head_right.setTexture(snake_head_image_right);

   sf::Texture applepic;
   applepic.loadFromFile("images/apple.png");
   sf::Sprite apple;
   apple.setTexture(applepic);

   for (int i = 0; i < field_for_y; i++)
      for (int j = 0; j < field_for_x; j++) {

         /*
             * отрисовка поля в клеточку
          */

         if (i % 2 == j % 2) {
            based2.setPosition(j * size_pixel, i * size_pixel);
            window.draw(based2);
         } else {
            based1.setPosition(j * size_pixel, i * size_pixel);
            window.draw(based1);
         }

         /*
             * отрисовка змейки и ее головы в различных направлениях
          */

         if (mainfield[i][j] > 0) {

            int ma = 0;
            for (int z1 = 0; z1 < field_for_y; z1++) {
               for (int z2 = 0; z2 < field_for_x; z2++) {
                  if (mainfield[z1][z2] > ma) {
                     ma = mainfield[z1][z2];
                  }
               }
            }

            snake.setPosition(j * size_pixel, i * size_pixel);
            window.draw(snake);

            if (mainfield[i][j] == ma) {
               if (basedirection == "up") {
                  snake_head_up.setPosition(j * size_pixel, i * size_pixel);
                  window.draw(snake_head_up);
               }
               if (basedirection == "down") {
                  snake_head_down.setPosition(j * size_pixel, i * size_pixel);
                  window.draw(snake_head_down);
               }
               if (basedirection == "left") {
                  snake_head_left.setPosition(j * size_pixel, i * size_pixel);
                  window.draw(snake_head_left);
               }
               if (basedirection == "right") {
                  snake_head_right.setPosition(j * size_pixel, i * size_pixel);
                  window.draw(snake_head_right);
               }
            }
         }

         /*
             * отрисовка яблока
          */

         if (mainfield[i][j] == -1) {
            apple.setPosition(j * size_pixel, i * size_pixel);
            window.draw(apple);
         }
      }
}

/*
 * функция изменения направления змейки
 * проверка возможности хода в другом направлении
 */
void game_control() {
   if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::W)) and
       basedirection != "down") {
      basedirection = "up";
   }
   if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or sf::Keyboard::isKeyPressed(sf::Keyboard::S)) and
       basedirection != "up") {
      basedirection = "down";
   }
   if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::A)) and
       basedirection != "right") {
      basedirection = "left";
   }
   if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::D)) and
       basedirection != "left") {
      basedirection = "right";
   }
}

/*
 * изначальная отрисовка поля и заполнение массива
 */

void change_area() {
   zero_vector();
   snake_pos();
   creating_apple();
}

int main() {
   change_area();

   const int height_of_window = field_for_y * size_pixel; // высота окна
   const int width_of_window = field_for_x * size_pixel; // длина окна

   // рендер окна

   sf::RenderWindow window(sf::VideoMode(width_of_window, height_of_window), "Snake game");

   // выполнение условий пока окно открыто, если игра завершается, то оно закрывается

   while (window.isOpen()) {
      sf::Event event;
      while (window.pollEvent(event)) {
         if (event.type == sf::Event::Closed)
            window.close();
      }

      if (flag)
         window.close();

      moving_snake();
      window.clear();
      draw_area(window);
      game_control();
      window.display();
      sf::sleep(sf::milliseconds(200));

   }

   return 0;
}
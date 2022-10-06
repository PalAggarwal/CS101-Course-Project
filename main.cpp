#include <simplecpp>
#include "shooter.h"
#include "bubble.h"

/* Simulation Vars */
const double STEP_TIME = 0.02;

/* Game Vars */
const int PLAY_Y_HEIGHT = 450;
const int LEFT_MARGIN = 70;
const int TOP_MARGIN = 20;
const int BOTTOM_MARGIN = (PLAY_Y_HEIGHT+TOP_MARGIN);


void move_bullets(vector<Bullet> &bullets){
    // move all bullets
    for(unsigned int i=0; i<bullets.size(); i++){
        if(!bullets[i].nextStep(STEP_TIME)){
            bullets.erase(bullets.begin()+i);
        }
    }
}

void move_bubbles(vector<Bubble> &bubbles){
    // move all bubbles
    for (unsigned int i=0; i < bubbles.size(); i++)
    {
        bubbles[i].nextStep(STEP_TIME);
    }
}

void erase_bubbles(vector<Bubble> &bubbles, vector<Bullet> &bullets){
    //erase bubble if hit by bullet
    for (unsigned int i=0; i < bubbles.size(); i++)
    {
      for (unsigned int j=0; j < bullets.size(); j++)
      {
        if (bubbles[i].get_radius()<=10){
        if ( abs(bullets[j].get_center_y() - bubbles[i].get_center_y()) < bubbles[i].get_radius() + 10
              && abs(bullets[j].get_center_x() - bubbles[i].get_center_x()) < bubbles[i].get_radius() + 10){
          bubbles.erase(bubbles.begin()+i);
          }
        }
      }
    }
}

void divide_bubbles(vector<Bubble> &bubbles, vector<Bullet> &bullets){
  //divide bubbles into smaller bubbles when hit by bullet
    for (unsigned int i=0; i < bubbles.size(); i++)
    {
      for (unsigned int j=0; j < bullets.size(); j++)
      {
        if (bubbles[i].get_radius()>10){
        if (abs(bullets[j].get_center_y() - bubbles[i].get_center_y()) < bubbles[i].get_radius() + 5
              && abs(bullets[j].get_center_x() - bubbles[i].get_center_x()) < bubbles[i].get_radius() + 5){
           double original_coordinate_x = bubbles[i].get_center_x();
           double original_coordinate_y = bubbles[i].get_center_y();
           double original_radius = bubbles[i].get_radius();
           double original_vx = bubbles[i].get_vx();
           bubbles.erase(bubbles.begin()+i);
           bubbles.push_back(Bubble(original_coordinate_x+50, original_coordinate_y, original_radius/2.0, original_vx, 50, COLOR(255, 105, 180)));
           bubbles.push_back(Bubble(original_coordinate_x-50, original_coordinate_y, original_radius/2.0, -original_vx, 50, COLOR(255, 105, 180)));
           break;
          }
        }
      }
    }
}

void divide_bubbles3(vector<Bubble> &bubbles, vector<Bullet> &bullets){
  //divide bubbles into smaller bubbles when hit by bullet
    for (unsigned int i=0; i < bubbles.size(); i++)
    {
      for (unsigned int j=0; j < bullets.size(); j++)
      {
        if (bubbles[i].get_radius()>10){
        if (abs(bullets[j].get_center_y() - bubbles[i].get_center_y()) < bubbles[i].get_radius() + 5
              && abs(bullets[j].get_center_x() - bubbles[i].get_center_x()) < bubbles[i].get_radius() + 5){
           double original_coordinate_x = bubbles[i].get_center_x();
           double original_coordinate_y = bubbles[i].get_center_y();
           double original_radius = bubbles[i].get_radius();
           double original_vx = bubbles[i].get_vx();
           bubbles.erase(bubbles.begin()+i);
           bubbles.push_back(Bubble(original_coordinate_x+50, original_coordinate_y, original_radius/2.0, original_vx, 50, COLOR(0, 0, 255)));
           bubbles.push_back(Bubble(original_coordinate_x-50, original_coordinate_y, original_radius/2.0, -original_vx, 50, COLOR(0, 0, 255)));
           break;
          }
        }
      }
    }
}

vector<Bubble> create_bubbles()
{
    // create initial bubbles in the game
    vector<Bubble> bubbles;
    bubbles.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y, 20, -BUBBLE_DEFAULT_VX, 50, COLOR(255,105,180)));
    bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, 20, BUBBLE_DEFAULT_VX, 50, COLOR(255,105,180)));
    return bubbles;
}

vector<Bubble> create_bubbles2()
{
  // create initial bubbles for level 2 in the game
  vector<Bubble> bubbles2;
  bubbles2.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y, 10, -150, 50, COLOR(200,150,40)));
  bubbles2.push_back(Bubble(WINDOW_X/3.0, BUBBLE_START_Y, 10, 150, 50, COLOR(200,150,40)));
  bubbles2.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, 10, -150, 50, COLOR(200,150,40)));
  bubbles2.push_back(Bubble(WINDOW_X/5.0, BUBBLE_START_Y, 10, 150, 50, COLOR(200,150,40)));
  bubbles2.push_back(Bubble(WINDOW_X/1.5, BUBBLE_START_Y, 10, -150, 50, COLOR(200, 150, 40)));
  return bubbles2;
}

vector<Bubble> create_bubbles3()
{
  //create initial bubbles for level 3 in the game
  vector<Bubble> bubbles3;
  bubbles3.push_back(Bubble(WINDOW_X/1.1, BUBBLE_START_Y, 20, -200, 50, COLOR(0,0,255)));
  bubbles3.push_back(Bubble(WINDOW_X/1.5, BUBBLE_START_Y, 20, 200, 50, COLOR(0,0,255)));
  bubbles3.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y, 20, -200, 50, COLOR(0,0,255)));
  bubbles3.push_back(Bubble(WINDOW_X/3.0, BUBBLE_START_Y, 20, 200, 50, COLOR(0,0,255)));
  return bubbles3;
}

bool col_btw_shooter_bubble(vector<Bubble> &bubbles, Shooter shooter){
    bool answer=false;
    for (unsigned int i=0; i<bubbles.size(); i++){
       if ( abs(bubbles[i].get_center_x() - shooter.get_body_center_x()) < 9 + bubbles[i].get_radius()
           && abs(bubbles[i].get_center_y() - shooter.get_body_center_y()) < 31 + bubbles[i].get_radius() )
           answer = true;
      }
      return answer;
}

int main()
{
    initCanvas("Bubble Trouble", WINDOW_X, WINDOW_Y);

    Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
    b1.setColor(COLOR(0, 0, 255));

    string msg_cmd("Cmd: _");
    Text charPressed(LEFT_MARGIN, BOTTOM_MARGIN, msg_cmd);

    // Intialize the shooter
    Shooter shooter(SHOOTER_START_X, SHOOTER_START_Y, SHOOTER_VX);

    // Initialize the bubbles
    vector<Bubble> bubbles = create_bubbles();

    // Initialize the bullets (empty)
    vector<Bullet> bullets;

    XEvent event;

    bool completed_level_1 = false;
    bool completed_level_2 = false;



    // Main game loop
    while (true)
    {
        bool pendingEvent = checkEvent(event);
        if (pendingEvent)
        {
            // Get the key pressed
            char c = charFromEvent(event);
            msg_cmd[msg_cmd.length() - 1] = c;
            charPressed.setMessage(msg_cmd);

            // Update the shooter
            if(c == 'a')
                shooter.move(STEP_TIME, true);
            else if(c == 'd')
                shooter.move(STEP_TIME, false);
            else if(c == 'w')
                bullets.push_back(shooter.shoot());
            else if(c == 'q')
                return 0;
        }

        // Update the bubbles
        move_bubbles(bubbles);

        // Update the bullets
        move_bullets(bullets);

        divide_bubbles(bubbles, bullets);

        erase_bubbles(bubbles, bullets);

        if (col_btw_shooter_bubble(bubbles, shooter)) {
          for (unsigned int i=0; i<bubbles.size(); i++){
            bubbles[i].vx = 0;
            bubbles[i].vy = 0;
          }
          Text lose_message(WINDOW_X/2.0, WINDOW_Y/2.0, "Game Over");
          lose_message.imprint();
          break;
        }

        if (bubbles.size()==0) {
          Text win_message(WINDOW_X/2.0, WINDOW_Y/2.0, "Level 2");
          win_message.imprint();
          wait(1);
          completed_level_1 = true;
          break;
        }

        wait(STEP_TIME);
    }

    wait(1);

    if (completed_level_1)
    {
    Text space(WINDOW_X/2.0, WINDOW_Y/2.0, "            ");
    space.imprint();

    wait(2);

    // Initialize the bubbles
    vector<Bubble> bubbles2 = create_bubbles2();

    XEvent event2;

// Main game loop
    while (true)
    {
        bool pendingEvent = checkEvent(event2);
        if (pendingEvent)
        {
            // Get the key pressed
            char c = charFromEvent(event2);
            msg_cmd[msg_cmd.length() - 1] = c;
            charPressed.setMessage(msg_cmd);

            // Update the shooter
            if(c == 'a')
                shooter.move(STEP_TIME, true);
            else if(c == 'd')
                shooter.move(STEP_TIME, false);
            else if(c == 'w')
                bullets.push_back(shooter.shoot());
            else if(c == 'q')
                return 0;
        }

        // Update the bubbles
        move_bubbles(bubbles2);

        // Update the bullets
        move_bullets(bullets);

        erase_bubbles(bubbles2, bullets);

        if (col_btw_shooter_bubble(bubbles2, shooter)) {
          for (unsigned int i=0; i<bubbles2.size(); i++){
            bubbles2[i].vx = 0;
            bubbles2[i].vy = 0;
          }
          Text lose_message(WINDOW_X/2.0, WINDOW_Y/2.0-50, "Game Over");
          lose_message.imprint();
          break;
        }

       if (bubbles2.size()==0) {
          Text win_message2(WINDOW_X/2.0, WINDOW_Y/2.0, "Level 3");
          win_message2.imprint();
          wait(1);
          completed_level_2 = true;
          break;
        }

        wait(STEP_TIME);
    }
    }

    wait(1);

    if (completed_level_2)
    {
    Text space(WINDOW_X/2.0, WINDOW_Y/2.0, "            ");
    space.imprint();

    wait(2);

    // Initialize the bubbles
    vector<Bubble> bubbles3 = create_bubbles3();

    XEvent event3;

// Main game loop
    while (true)
    {
        bool pendingEvent = checkEvent(event3);
        if (pendingEvent)
        {
            // Get the key pressed
            char c = charFromEvent(event3);
            msg_cmd[msg_cmd.length() - 1] = c;
            charPressed.setMessage(msg_cmd);

            // Update the shooter
            if(c == 'a')
                shooter.move(STEP_TIME, true);
            else if(c == 'd')
                shooter.move(STEP_TIME, false);
            else if(c == 'w')
                bullets.push_back(shooter.shoot());
            else if(c == 'q')
                return 0;
        }

        // Update the bubbles
        move_bubbles(bubbles3);

        // Update the bullets
        move_bullets(bullets);

        divide_bubbles3(bubbles3, bullets);

        erase_bubbles(bubbles3, bullets);

        if (col_btw_shooter_bubble(bubbles3, shooter)) {
          for (unsigned int i=0; i<bubbles3.size(); i++){
            bubbles3[i].vx = 0;
            bubbles3[i].vy = 0;
          }
          Text lose_message(WINDOW_X/2.0, WINDOW_Y/2.0-50, "Game Over");
          lose_message.imprint();
          break;
        }

        if (bubbles3.size()==0) {
          Text win_message(WINDOW_X/2.0, WINDOW_Y/2.0-50, "Congratulations!! You Won");
          win_message.imprint();
          wait(2);
          break;
        }

        wait(STEP_TIME);
    }
  }

  wait(2);
}


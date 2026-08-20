 ad

# Base_ws

Este repositorio é dedicado a ser base de teleoperações

## ## `sensor_msgs/msg/joy.hpp`

boa parte dos codigos faram uso do topico joy , como subscriber ele permite controlar o tpico dsejado com um publisher. O codigo abaiuxo ilustra o mapeamento dos botoes em c++.

```c
   --- LEITURA DOS BOTÕES (BUTTONS) ---
    Index 0: A (CROSS), Index 1: B (CIRCLE), Index 2: X (SQUARE), Index 3: Y (TRIANGLE)
    bool button_cross    = msg->buttons[0];
    bool button_circle   = msg->buttons[1];
    bool button_square   = msg->buttons[2];
    bool button_triangle = msg->buttons[3];
  
    // Index 9: LEFTSHOULDER (L1), Index 10: RIGHTSHOULDER (R1)
    bool button_l1       = msg->buttons[9];
    // bool button_r1       = msg->buttons[10];

    // --- IMPRESSÃO DOS DADOS NO TERMINAL ---
    RCLCPP_INFO(this->get_logger(), "--- Estado do Controle ---");
    RCLCPP_INFO(this->get_logger(), "Analógico Esquerdo -> X: %.2f | Y: %.2f", left_stick_x, left_stick_y);
    RCLCPP_INFO(this->get_logger(), "Analógico Direito  -> X: %.2f | Y: %.2f", right_stick_x, right_stick_y);
    RCLCPP_INFO(this->get_logger(), "Gatilhos           -> L2: %.2f | R2: %.2f", trigger_l2, trigger_r2);

    // Exibe apenas se algum dos botões principais estiver pressionado
    if (button_cross)    RCLCPP_INFO(this->get_logger(), "Botão pressionado: [ X (CROSS) ]");
    if (button_circle)   RCLCPP_INFO(this->get_logger(), "Botão pressionado: [ O (CIRCLE) ]");
    if (button_square)   RCLCPP_INFO(this->get_logger(), "Botão pressionado: [ Quadrado (SQUARE) ]");
    if (button_triangle) RCLCPP_INFO(this->get_logger(), "Botão pressionado: [ Triângulo (TRIANGLE) ]");
    if (button_l1)       RCLCPP_INFO(this->get_logger(), "Botão pressionado: [ L1 ]");
    if (button_r1)       RCLCPP_INFO(this->get_logger(), "Botão pressionado: [ R1 ]");
```

# base_ws

as

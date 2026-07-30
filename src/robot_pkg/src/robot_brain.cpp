#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "std_msgs/msg/int32.hpp"

class PS4ControllerNode : public rclcpp::Node
{
public:
  PS4ControllerNode() : Node("ps4_controller_node")
  {
    subscription_joy = this->create_subscription<sensor_msgs::msg::Joy>(
      "/joy", 10, std::bind(&PS4ControllerNode::joy_callback, this, std::placeholders::_1)
    );

    publisher_state_ = this->create_publisher<std_msgs::msg::Int32>("/esp32/motor_state", 10);
    publisher_vel_   = this->create_publisher<std_msgs::msg::Int32>("/esp32/robot_vel", 10);

    RCLCPP_INFO(this->get_logger(), "Nó de leitura do controle de PS4 iniciado.");
  }

private:
  int robot_vel_ = 128; // Velocidade inicial padrão (em 50%)
  const int VELOCIDADE_MAX = 255;
  const int VELOCIDADE_MIN = 0;

  void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg) 
  {
    auto msg_state = std_msgs::msg::Int32();
    auto msg_vel   = std_msgs::msg::Int32();

    // --- LEITURA DOS EIXOS ---
    float left_stick_y  = msg->axes[1]; // Frente / Trás
    float right_stick_x = msg->axes[2]; // Esquerda / Direita
    float trigger_l2    = msg->axes[4]; // Vai de 1.0 (solto) até -1.0 (apertado)

    // --- LEITURA DOS BOTÕES ---
    bool button_l1 = msg->buttons[9];

    // --- LÓGICA DE MOVIMENTO (Prioridades sem sobrescrever) ---
    // Checa primeiro o Analógico Esquerdo (Frente / Trás)
    if (left_stick_y > 0.2f) {
      msg_state.data = 1;  // Frente
    } else if (left_stick_y < -0.2f) {
      msg_state.data = -1; // Trás
    } 
    // Se o esquerdo estiver no centro, checa o Direito (Giro/Curva)
    else if (right_stick_x > 0.2f) {
      msg_state.data = 2;  // Direita
    } else if (right_stick_x < -0.2f) {
      msg_state.data = -2; // Esquerda
    } 
    else {
      msg_state.data = 0;  // Parado
    }

    // --- LÓGICA DE VELOCIDADE ---
    bool vel_alterada = false;

    // Aumentar velocidade com L1
    if (button_l1) {
      if (robot_vel_ < VELOCIDADE_MAX) {
        robot_vel_ += 10;
        if (robot_vel_ > VELOCIDADE_MAX) robot_vel_ = VELOCIDADE_MAX;
        RCLCPP_INFO(this->get_logger(), "Velocidade Aumentada: %d", robot_vel_);
      } else {
        RCLCPP_WARN(this->get_logger(), "Velocidade MÁXIMA atingida (%d)!", robot_vel_);
      }
      vel_alterada = true;
    }

    // Diminuir velocidade com Gatilho L2 (Pressionado quando < 0.0)
    if (trigger_l2 < 0.0f) {
      if (robot_vel_ > VELOCIDADE_MIN) {
        robot_vel_ -= 10;
        if (robot_vel_ < VELOCIDADE_MIN) robot_vel_ = VELOCIDADE_MIN;
        RCLCPP_INFO(this->get_logger(), "Velocidade Reduzida: %d", robot_vel_);
      } else {
        RCLCPP_WARN(this->get_logger(), "Velocidade MÍNIMA atingida (%d)!", robot_vel_);
      }
      vel_alterada = true;
    }

    // Publica o estado do motor
    publisher_state_->publish(msg_state);

    // Publica a velocidade (Sempre envia a velocidade atual para manter o ESP32 atualizado)
    msg_vel.data = robot_vel_;
    publisher_vel_->publish(msg_vel);
  }

  rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_joy;
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_state_;
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_vel_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PS4ControllerNode>());
  rclcpp::shutdown();
  return 0;
}
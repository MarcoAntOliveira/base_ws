// #include "rclcpp/rclcpp.hpp"


// using namespace std::placeholders;

// class MotorControlServerNode : public rclcpp::Node
// {
// public:
//     RobotNode() : Node("robot_server_node")
//     {
//         // Criação do serviço 'set_motor_speeds'
//         // request->a  = PWM/Velocidade Motor Esquerdo (-255 a 255)
//         // request->b  = PWM/Velocidade Motor Direito  (-255 a 255)
//         server_ = this->create_service<base_interfaces::srv::AddTwoInts>(
//             "set_motor_speeds",
//             std::bind(&MotorControlServerNode::callbackSetMotorSpeeds, this, _1, _2));
            

//         RCLCPP_INFO(this->get_logger(), "Servico de Controle de Motores iniciado e aguardando chamadas.");
//     }

// private:
//     void callbackSetMotorSpeeds(
//         const base_interfaces::srv::AddTwoInts::Request::SharedPtr request,
//         const base_interfaces::srv::AddTwoInts::Response::SharedPtr response)
//     {
//         // 1. Extrai e limita os valores recebidos aos limites do PWM (ex: -255 a 255)
//         int target_pwm_left = std::clamp(static_cast<int>(request->a), -255, 255);
//         int target_pwm_right = std::clamp(static_cast<int>(request->b), -255, 255);

//         // 2. Atualiza o estado interno do nó
//         pwm_left_ = target_pwm_left;
//         pwm_right_ = target_pwm_right;

//         // 3. (Opcional) Aqui você chamaria a função física de hardware se estivesse rodando diretamente no ESP32/SBC
//         // updateHardwarePWM(pwm_left_, pwm_right_);

//         // 4. Preenche a resposta do serviço
//         response->sum = (pwm_left_ != 0 || pwm_right_ != 0) ? 1 : 0; // 1 = Motores Ativos, 0 = Parados

//         RCLCPP_INFO(this->get_logger(), 
//             "Estados dos Motores Atualizados -> Esquerdo: %d | Direito: %d", 
//             pwm_left_, pwm_right_);
//     }

//     // Variáveis de estado do motor
//     int pwm_left_{0};
//     int pwm_right_{0};

//     rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr server_;
// };

// int main(int argc, char **argv)
// {
//     rclcpp::init(argc, argv);
//     auto node = std::make_shared<MotorControlServerNode>();
//     rclcpp::spin(node);
//     rclcpp::shutdown();
//     return 0;
// }

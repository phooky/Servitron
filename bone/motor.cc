#include "motor.h"
#include "util.h"
#include "config.h"

const std::string enable_pin = "servitron:m_en";

const std::string pwm_prefix = "/sys/devices/ocp.2/";
const std::string pwm_suffix = "/duty";

class MotorImpl {
private:
  LedOut m_a, m_b, m_en;
  std::ofstream m_duty_stream;
public:
  MotorImpl(const std::string& a,
            const std::string& b,
            const std::string& en,
            const std::string& pwm) :
    m_a(a), m_b(b), m_en(en) {
    m_duty_stream.open((pwm_prefix + pwm + pwm_suffix).c_str());
    m_en.set(0);
  }
  ~MotorImpl() {
    m_duty_stream.close();
  }
  void setPower(int value) {
    m_en.set((value == 0)?0:1);
    
    if (value > 0) {
      m_b.set(0);
      m_a.set(1);
      m_en.set(1);
      m_duty_stream << value << std::endl;
    } else if (value < 0) {
      m_a.set(0);
      m_b.set(1);
      m_en.set(1);
      m_duty_stream << -value << std::endl;
    } else if (value == 0) {
      m_a.set(0);
      m_b.set(0);
      m_en.set(0);
      m_duty_stream << value << std::endl;
    }
  }
};

Motors::Motors() : m_en(enable_pin)
{
  m_impl[0] = new MotorImpl("servitron:m0_a",
                            "servitron:m0_b",
                            "servitron:m0_en",
                            "motor_pwm1b.15");
  m_impl[1] = new MotorImpl("servitron:m1_a",
                            "servitron:m1_b",
                            "servitron:m1_en",
                            "motor_pwm1a.14");
  m_impl[2] = new MotorImpl("servitron:m2_a",
                            "servitron:m2_b",
                            "servitron:m2_en",
                            "motor_pwm0a.12");
  m_impl[3] = new MotorImpl("servitron:m3_a",
                            "servitron:m3_b",
                            "servitron:m3_en",
                            "motor_pwm0b.13");
  m_impl[4] = new MotorImpl("servitron:m4_a",
                            "servitron:m4_b",
                            "servitron:m4_en",
                            "motor_pwm2a.16");
  m_impl[5] = new MotorImpl("servitron:m5_a",
                            "servitron:m5_b",
                            "servitron:m5_en",
                            "motor_pwm2b.17");
  m_en.set(1);
}

Motors::~Motors() {
  enable(false);
  for (int i = 0; i < 6; i++) { 
    m_impl[i]->setPower(0);
    delete m_impl[i]; 
    m_impl[i] = 0; 
  }
}

void Motors::enable(bool en) {
  m_en.set(en?0:1);
}


// Set the motor to the specified
// power. 0 is off. Negative values are CCW, positive
// are CW.
void Motors::setPower(int channel, int value) {
  m_impl[channel]->setPower(value);
}
    


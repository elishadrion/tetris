#ifndef __SETTING_KEY__HPP__
#define __SETTING_KEY__HPP__

class SettingKeys{
  private:
    // current key setting
    std::string C_rotateRigth;
    std::string C_rotateLeft;
    std::string C_accelerate;
    std::string C_moveRigth;
    std::string C_moveLeft;
    std::string C_hardDrop;
    std::string C_hold;

  public:
    SettingKeys();

    ~SettingKeys(); // pour fermer le fichier

    void RotateRigth(std::string keyID);

    void dispalyCurrentKeys();

    void RotateLeft(std::string keyID);

    void accelerate(std::string keyID);

    void moveRigth(std::string keyID);

    void moveLeft(std::string keyID);

    void hardDrop(std::string keyID);

    void hold(std::string keyID);

    void saveSettings();

};


#endif


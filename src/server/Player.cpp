#include "Player.hpp"

Player::Player(std::string username, int sockfd): _username(username), _playerConnect(new PlayerConnect(sockfd, this)) {}

unsigned Player::get_ratio() const {
    unsigned res = 0;
    unsigned total = get_victories()+get_defeats();
    if(total > 0) {
        res = get_victories()/total;
    }

    return res;
}

void Player::set_sockfd(int sockfd) {_playerConnect->set_sockfd(sockfd);}

bool Player::operator<(const Player &other) const {
    return this->get_ratio() < other.get_ratio();
}

bool Player::operator>(const Player &other) const {
    return !((*this) < other);
}

bool Player::operator==(const std::string &other_name) const {
    return ((*this).get_name() == other_name);
}

void Player::send_packet(Packet::packet *packet, size_t size) {
    _playerConnect->send_packet(packet, size);
}

void Player::receive() {
    _playerConnect->receive();
}

void Player::logout() {
    _playerConnect->logout();
}

/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2024 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#pragma once

#include <utility>

#include "creatures/creatures_definitions.hpp"
#include "enums/player_cyclopedia.hpp"
#include "enums/account_group_type.hpp"

class Player;
class KV;

struct Title {
	uint8_t m_id = 0;
	CyclopediaTitle_t m_type = CyclopediaTitle_t::NOTHING;
	std::string m_maleName;
	std::string m_femaleName;
	std::string m_description;
	uint32_t m_amount = 0;
	bool m_permanent = false;
	uint8_t m_skill = 0;
	uint16_t m_race = 0;

	Title() = default;

	Title(uint8_t id, CyclopediaTitle_t type, std::string maleName, std::string description, uint32_t amount, bool permanent) :
		m_id(id), m_type(type), m_maleName(std::move(maleName)), m_description(std::move(description)), m_amount(amount),
		m_permanent(permanent) { }

	Title(uint8_t id, CyclopediaTitle_t type, std::string maleName, std::string description, uint32_t amount, bool permanent, std::string femaleName) :
		m_id(id), m_type(type), m_maleName(std::move(maleName)), m_description(std::move(description)), m_amount(amount),
		m_permanent(permanent), m_femaleName(std::move(femaleName)) { }

	Title(uint8_t id, CyclopediaTitle_t type, std::string maleName, std::string femaleName, std::string description, uint8_t skill) :
		m_id(id), m_type(type), m_maleName(std::move(maleName)), m_femaleName(std::move(femaleName)), m_description(std::move(description)),
		m_skill(skill) { }

	Title(uint8_t id, CyclopediaTitle_t type, uint16_t race, std::string maleName, std::string femaleName, std::string description) :
		m_id(id), m_type(type), m_race(race), m_maleName(std::move(maleName)), m_femaleName(std::move(femaleName)),
		m_description(std::move(description)) { }

	Title(uint8_t id, CyclopediaTitle_t type, uint16_t race, std::string maleName, std::string femaleName, std::string description, uint32_t amount, bool permanent) :
		m_id(id), m_type(type), m_race(race), m_maleName(std::move(maleName)), m_femaleName(std::move(femaleName)),
		m_description(std::move(description)), m_amount(amount), m_permanent(permanent) { }

	Title(uint8_t id, CyclopediaTitle_t type, std::string maleName, std::string description, bool permanent) :
		m_id(id), m_type(type), m_maleName(std::move(maleName)), m_description(std::move(description)), m_permanent(permanent) { }

	bool operator==(const Title &other) const {
		return m_id == other.m_id;
	}
};

namespace std {
	template <>
	struct hash<Title> {
		std::size_t operator()(const Title &t) const {
			return hash<uint8_t>()(t.m_id);
		}
	};
}

class PlayerTitle {
public:
	explicit PlayerTitle(Player &player);

	[[nodiscard]] bool isTitleUnlocked(uint8_t id) const;
	bool manage(bool canAdd, uint8_t id, uint32_t timestamp = 0);
	void remove(const Title &title);
	const std::vector<std::pair<Title, uint32_t>> &getUnlockedTitles();
	[[nodiscard]] uint8_t getCurrentTitle() const;
	void setCurrentTitle(uint8_t id);
	std::string getCurrentTitleName();
	static const std::string &getNameBySex(PlayerSex_t sex, const std::string &male, const std::string &female);
	void checkAndUpdateNewTitles();
	void loadUnlockedTitles();
	const std::shared_ptr<KV> &getUnlockedKV();

	// Title Calculate Functions
	bool checkGold(uint32_t amount);
	bool checkMount(uint32_t amount);
	bool checkOutfit(uint32_t amount);
	bool checkLevel(uint32_t amount);
	bool checkHighscore(uint8_t skill);
	bool checkBestiary(const std::string &name, uint16_t race, bool isBoss = false, uint32_t amount = 0);
	bool checkLoginStreak(uint32_t amount);
	bool checkTask(uint32_t amount);
	bool checkMap(uint32_t amount);
	bool checkOther(const std::string &name);

private:
	// {title ID, time when it was unlocked}
	std::shared_ptr<KV> m_titleUnlockedKV;
	std::vector<std::pair<Title, uint32_t>> m_titlesUnlocked;
	Player &m_player;
};

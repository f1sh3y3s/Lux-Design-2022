#include "lux/unit.hpp"

#include <cmath>

#include "lux/config.hpp"
#include "lux/exception.hpp"
#include "lux/observation.hpp"

namespace lux {

    int64_t Unit::actionQueueCost(const Observation &obs) const {
        auto cost    = unitConfig.ACTION_QUEUE_POWER_COST;
        auto weather = obs.getCurrentWeather();
        return cost * weather.POWER_CONSUMPTION;
    }

    int64_t Unit::moveCost(const Observation &obs, Direction direction) const {
        Position target = pos + Position::Delta(direction);
        if (target.x < 0 || target.y < 0 || static_cast<size_t>(target.x) >= obs.board.rubble.size()
            || static_cast<size_t>(target.y) >= obs.board.rubble.size()) {
            return -1;
        }
        const std::string player = team_id == 0 ? "player_0" : "player_1";
        LUX_ASSERT(obs.teams.find(player) != obs.teams.end(), "must find fitting team");
        const auto &strains        = obs.teams.find(player)->second.factory_strains;
        int64_t     strainAtTarget = obs.board.factory_occupancy[target.x][target.y];
        if (strainAtTarget != -1 && std::none_of(strains.begin(), strains.end(), [strainAtTarget](int64_t s) -> bool {
                return s == strainAtTarget;
            })) {
            return -1;
        }
        auto rubble  = obs.board.rubble[target.x][target.y];
        auto weather = obs.getCurrentWeather();
        return std::ceil((unitConfig.MOVE_COST + unitConfig.RUBBLE_MOVEMENT_COST * rubble) * weather.POWER_CONSUMPTION);
    }

    UnitAction Unit::move(Direction direction, int64_t repeat) const { return UnitAction::Move(direction, repeat); }

    UnitAction Unit::transfer(Direction direction, Resource resource, int64_t amount, int64_t repeat) const {
        return UnitAction::Transfer(direction, resource, amount, repeat);
    }

    UnitAction Unit::pickup(Resource resource, int64_t amount, int64_t repeat) const {
        return UnitAction::Pickup(resource, amount, repeat);
    }

    int64_t Unit::digCost(const Observation &obs) const {
        auto weather = obs.getCurrentWeather();
        return std::ceil(unitConfig.DIG_COST * weather.POWER_CONSUMPTION);
    }

    UnitAction Unit::dig(int64_t repeat) const { return UnitAction::Dig(repeat); }

    int64_t Unit::selfDestructCost(const Observation &obs) const {
        auto weather = obs.getCurrentWeather();
        return std::ceil(unitConfig.SELF_DESTRUCT_COST * weather.POWER_CONSUMPTION);
    }

    UnitAction Unit::selfDestruct(int64_t repeat) const { return UnitAction::SelfDestruct(repeat); }

    UnitAction Unit::recharge(int64_t amount, int64_t repeat) const { return UnitAction::Recharge(amount, repeat); }
}  // namespace lux

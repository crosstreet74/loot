/*  LOOT

A load order optimisation tool for Oblivion, Skyrim, Fallout 3 and
Fallout: New Vegas.

Copyright (C) 2014-2018    WrinklyNinja

This file is part of LOOT.

LOOT is free software: you can redistribute
it and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

LOOT is distributed in the hope that it will
be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LOOT.  If not, see
<https://www.gnu.org/licenses/>.
*/

#ifndef LOOT_GUI_QUERY_APPLY_SORT_QUERY
#define LOOT_GUI_QUERY_APPLY_SORT_QUERY

#include "gui/cef/query/query.h"

namespace loot {
class ApplySortQuery : public Query {
public:
  ApplySortQuery(LootState& state, const std::vector<std::string>& plugins) :
      state_(state),
      plugins_(plugins) {}

  std::string executeLogic() {
    auto logger = state_.getLogger();
    if (logger) {
      logger->trace("User has accepted sorted load order, applying it.");
    }
    try {
      state_.getCurrentGame().SetLoadOrder(plugins_);
      state_.decrementUnappliedChangeCounter();
    }
    catch (...) {
      setErrorMessage(boost::locale::translate(
        "Oh no, something went wrong! This is usually because your "
        "plugins.txt is set to be read-only. If it is, unset it and "
        "try again. If it isn't, you can check your LOOTDebugLog.txt "
        "(you can get to it through the main menu) for more information.")
        .str());
      throw;
    }

    return "";
  }

private:
  LootState& state_;
  const std::vector<std::string> plugins_;
};
}

#endif

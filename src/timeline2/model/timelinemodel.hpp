/***************************************************************************
 *   Copyright (C) 2017 by Nicolas Carion                                  *
 *   This file is part of Kdenlive. See www.kdenlive.org.                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3 or any later version accepted by the       *
 *   membership of KDE e.V. (or its successor approved  by the membership  *
 *   of KDE e.V.), which shall act as a proxy defined in Section 14 of     *
 *   version 3 of the license.                                             *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#include <memory>
#include <unordered_map>
#include <QVector>
#include <mlt++/MltTractor.h>

class TrackModel;

/* @brief This class represents a Timeline object, as viewed by the backend.
   In general, the Gui associated with it will send modification queries (such as resize or move), and this class authorize them or not depending on the validity of the modifications
*/
class TimelineModel
{
public:
    TimelineModel();

    friend class TrackModel;

    /* @brief returns the number of tracks */
    int getTracksNumber();
protected:
    /* @brief Register a new track. This is a call-back meant to be called from TrackModel
       @param pos indicates the number of the track we are adding. If this is -1, then we add at the end.
     */
    void registerTrack(std::unique_ptr<TrackModel>&& track, int pos = -1);

    /* @brief Deregister and destruct the track with given id.
     */
    void deregisterTrack(int id);
private:
    Mlt::Tractor m_tractor;
    QVector<int> m_snapPoints; // this will be modified from a lot of different places, we will probably need a mutex

    std::list<std::unique_ptr<TrackModel>> m_allTracks;

    std::unordered_map<int, std::list<std::unique_ptr<TrackModel>>::iterator> m_iteratorTable; //this logs the iterator associated which each track id. This allows easy access of a track based on its id.

};

/*
 * MicroHH
 * Copyright (c) 2011-2017 Chiel van Heerwaarden
 * Copyright (c) 2011-2017 Thijs Heus
 * Copyright (c) 2014-2017 Bart van Stratum
 *
 * This file is part of MicroHH
 *
 * MicroHH is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * MicroHH is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with MicroHH.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MODEL
#define MODEL

#include <string>
#include <memory>
#include <thread>

class Master;
class Input;
class Data_block;

template<typename> class Grid;
template<typename> class Fields;

template<typename> class Field3d_operators;
template<typename> class Timeloop;
template<typename> class Boundary;
template<typename> class Advec;
template<typename> class Diff;
template<typename> class Pres;
template<typename> class Force;
template<typename> class Decay;

template<typename> class Stats;
template<typename> class Column;
template<typename> class Cross;
template<typename> class Dump;

enum class Sim_mode;

template<typename TF>
class Model
{
    public:
        Model(Master&, int, char**);
        ~Model();

        void init();
        void load_or_save();
        void exec();

    private:
        Master& master;

        std::shared_ptr<Input> input;
        std::shared_ptr<Data_block> profs;

        std::shared_ptr<Grid<TF>> grid;
        std::shared_ptr<Fields<TF>> fields;

        std::shared_ptr<Field3d_operators<TF>> field3d_operators;
        std::shared_ptr<Timeloop<TF>> timeloop;
        std::shared_ptr<Boundary<TF>> boundary;
        std::shared_ptr<Advec<TF>> advec;
        std::shared_ptr<Diff<TF>> diff;
        std::shared_ptr<Pres<TF>> pres;
        std::shared_ptr<Force<TF>> force;
        std::shared_ptr<Decay<TF>> decay;

        std::shared_ptr<Stats<TF>> stats;
        std::shared_ptr<Column<TF>> column;
        std::shared_ptr<Cross<TF>> cross;
        std::shared_ptr<Dump<TF>> dump;
        Sim_mode sim_mode;
        std::string sim_name;

        void load();
        void save();

        void delete_objects();
        void print_status();
        void calculate_statistics(int, double, unsigned long, int);
        void set_time_step();

        void prepare_gpu();
        void clear_gpu();

        void add_statistics_masks();

        #ifdef USECUDA
        std::thread t_stat;
        #endif

};
#endif

/*
 *  Copyright (C) 2015, 2016 University of Leeds
    Copyright (C) 2016, UCL
    This file is part of STIR.

    This file is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This file is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    See STIR/LICENSE.txt for details
*/
/*!
  \file
  \ingroup listmode
  \brief Declaration of class stir::ecat::CListModeDataROOT

  \author Nikos Efthimiou
*/

#ifndef __stir_listmode_CListModeDataROOT_H__
#define __stir_listmode_CListModeDataROOT_H__

#include "stir/listmode/CListModeData.h"
#include "stir/listmode/CListRecordROOT.h"
#include "stir/IO/InputStreamWithRecords.h"
#include "stir/IO/InputStreamFromROOTFile.h"
#include "stir/shared_ptr.h"
#include "stir/KeyParser.h"

#include <string>

START_NAMESPACE_STIR

//!
//! \brief The CListModeDataROOT class
//! \details A class that reads the listmode data for any scanner from ROOT files, generated by GATE
//! \author Nikos Efthimiou
//!
class CListModeDataROOT : public CListModeData
{
public:
    //! Construct fron the filename of the Interfile header
    CListModeDataROOT(const std::string& listmode_filename_prefix);

    virtual std::string
    get_name() const;

    virtual
    shared_ptr <CListRecord> get_empty_record_sptr() const;

    virtual
    Succeeded get_next_record(CListRecord& record) const;

    virtual
    Succeeded reset();

    virtual
    SavedPosition save_get_position();

    virtual
    Succeeded set_get_position(const SavedPosition&);

    virtual
    bool has_delayeds() const { return true; }

    //!
    //! \brief get_total_number_of_events
    //! \return Returns the total number of events in a ROOT file
    //! \author Nikos Efthimiou
    //!
    virtual
    long long int
    get_total_number_of_events() const ;

private:
    typedef CListRecordROOT CListRecordT;

    //! This function performs simple checks to validate that the repeaters,
    //! are consistent with the header file.
    Succeeded check_scanner_consistency();

    //! The header file, bad name choise.
    std::string listmode_filename;
    //! The root file
    std::string input_data_filename;
    //! Pointer to the listmode data
    shared_ptr<InputStreamFromROOTFile<CListRecordT, bool> > current_lm_data_ptr;

    //! The name of the originating scanner
    std::string originating_system;

    // Related to the Scanner
    //! Number of bins
    int num_bins;
    //! Bin size
    float bin_size;
    //! Physical inner ring radius
    float inner_ring_radius;
    //! Average depth of iteration
    float aver_depth_of_iteraction;
    //! Ring spacing
    float ring_spacing;
    //! Number of detector layers
    int num_det_layers;
    //!
    //! \brief singles_readout_depth
    //! \details This is a GATE parameters, defined in the digitizer. It
    //! defines the structure in which the energy summing is done.
    //! Value 4 means that each crystal is read individually.
    int singles_readout_depth;

    // These tell us something about how the listmode is stored.
    //! Span
    int axial_compression;
    //! S size of the sinogram
    int number_of_projections;
    //! Number of view in the sinogram
    int number_of_views;
    //! Number of segments.
    int number_of_segments;


//    shared_ptr<ProjDataInfo> proj_data_info_sptr;

    KeyParser parser;
    std::string name_of_input_tchain;

    //! Number of the rsectors used in the GATE mac file
    int number_of_rsectors;
    //! The x axis would indicate mupliple layers
    int number_of_modules_x;
    //! The y axis indicates the tangestial position
    int number_of_modules_y;
    //! The z axis is the axial
    int number_of_modules_z;

    //! Number of submodules x in the GATE mac file
    int number_of_submodules_x;
    //! Submodule y repeater in the GATE mac file
    int number_of_submodules_y;
    //! Submodule z repeater in the GATE mac file
    int number_of_submodules_z;
    //! Crystal x repeater in the GATE mac file
    int number_of_crystals_x;
    //! Crystla y repeater in the GATE mac file
    int number_of_crystals_y;
    //! Crystal z repeater in the GATE mac file
    int number_of_crystals_z;
    //! Number of detectors to rotate, if the user has used default GATE
    //! geometry, first block in phi = 0, then this should be zero, to
    //! align with STIR.
    int offset_dets;

    //! Total number of events in the ROOT file
    long long int total_number_of_events;

    //! If set all scattered events will be excluded
    bool exclude_scattered;
    //! If set all random event will be excluded
    bool exclude_randoms;

    //! The low energy window threshold
    //! \warning When ExamData are merged it will be removed
    float low_energy_window;
    //! The upper energy window threshold
    //! \warning When ExamData are merged it will be removed
    float up_energy_window;

    Succeeded open_lm_file();

    //!
    //! \brief read_frames_info
    //! \details This function is stolen from InterfileHeader.cxx
    void read_frames_info();

     int num_time_frames;
     double _image_relative_start_times;
     double _image_durations;

     std::vector<double> image_relative_start_times;
     std::vector<double> image_durations;

};


END_NAMESPACE_STIR

#endif

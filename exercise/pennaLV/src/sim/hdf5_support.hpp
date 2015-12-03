/** ****************************************************************************
 * 
 * \file
 * \brief Simulation HDF5 Support
 * \author Programming Techniques for Scientific Simulations II, ETH Zürich
 * \date 2015
 * \copyright Licensed under the Apache License. See COPYING for details.
 * 
 ******************************************************************************/

#ifndef SIM_HDF5_SUPPORT_HEADER
#define SIM_HDF5_SUPPORT_HEADER

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <map>

#include "hdf5.h"

/// \cond IMPLEMENTATION_DETAIL_DOC
namespace detail {
    void write_attribute(hid_t const & dataset_id, std::string const & name, int const & val) {
        if(H5Aexists(dataset_id, name.c_str())) {
            throw std::runtime_error("attribute " + name + " already exists");
            return;
        }
        
        hsize_t dims[] = {1};
        auto dataspace_id = H5Screate_simple(1, dims, NULL);
        hid_t attribute_id;
        attribute_id = H5Acreate2 (dataset_id, name.c_str(), H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT);
        H5Awrite(attribute_id, H5T_NATIVE_INT, &val);
        H5Sclose(dataspace_id);
        H5Aclose(attribute_id);
    }
    
    template<typename T>
    hid_t write_dataset( hid_t const & file_id
                       , std::string const & name
                       , T data) {
        
        if(H5Lexists(file_id, ("/"+name).c_str(), H5P_DEFAULT)) {
            throw std::runtime_error("dataset " + ("/"+name) + " already exists");
            return 0;
        }
        
        hsize_t dims[] = {data.size(), data[0].size()};
        // copy data to a c-array
        std::unique_ptr<int[]> buf(new int[dims[0]*dims[1]]);
        std::size_t i = 0;
        for(auto const & line: data)
            for(auto const & elem: line)
                buf[i++] = elem;
        
        auto dataspace_id = H5Screate_simple(2, dims, nullptr);
        hid_t dataset_id;
        
        dataset_id = H5Dcreate2(file_id, ("/"+name).c_str(), H5T_STD_I32BE, dataspace_id, 
                              H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        H5Dwrite(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, 
                         buf.get());
        H5Sclose(dataspace_id);
        return dataset_id;
    }

    hid_t open_file(std::string const & name) {
        std::ifstream f(name.c_str());
        bool exists = f.good();
        f.close();
        if(exists)
            return H5Fopen(name.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);
        else
            return H5Fcreate(name.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    }
}//end namespace detail
/// \endcond

/**\brief writes the solution of a pennaLV simulation to HDF5
 * \param filename  should be a filename where the simulation-output should 
 *        be written to. If the file arleady exists, new results will be appended. 
 * \param dsetname is the name for the dataset. If it already exists, an error will be thrown
 *        to avoid unintentional overwrite.
 * \param data  a matrix-like object that holds the measurement-values
 * \param attr  is a map of strings and just holds parameter that 
 *        should be written to the hdf5 dataset.
 * */
template<typename T>
void to_hdf5( std::string const & filename
            , std::string const & dsetname
            , T data
            , std::map<std::string, int> attr) {
    
    // open/create dataset and file
    auto file_id = detail::open_file(filename);
    auto dataset_id = detail::write_dataset(file_id, dsetname, data); // throws if name exists
    
    for(auto const & a: attr) {
        detail::write_attribute(dataset_id, a.first, a.second); // throws if name exists
    }

    // close dataset and file
    H5Dclose(dataset_id);
    H5Fclose(file_id);
}

#endif //SIM_HDF5_SUPPORT_HEADER

#include <H5Cpp.h> // Importing the HDF5 library
#include <iostream>
#include <string>

const std::string FILE_NAME("data.h5"); 
const std::string GROUP_NAME("my_group");
const std::string DATASET_NAME("my_dataset");

int main() {
    try {
        // Creating a file /////////////////////////////////////////
        // Creating an HDF5 file
        H5::H5File file(FILE_NAME, H5F_ACC_TRUNC);

        /*
        The second entry possible values for H5::H5File are:
        - H5F_ACC_TRUNC to overwrite the content of the file if it 
                        already exists
        - H5F_ACC_RDONLY for read-only mode
        - H5F_ACC_RDWR for read and write mode
        - H5F_ACC_EXCL to create the file only if it does not exist
        */

        // Creating a group /////////////////////////////////////////////
        H5::Group group = file.createGroup(GROUP_NAME);
        
        // Creating a dataset inside the group ///////////////////////////
        
        /* Creating space for a matrix with 3 rows and 4 columns,
            using H5S_UNLIMITED to allow unlimited space for each 
            dimension, otherwise set maximum entries for each dimension
        */
        hsize_t dims[2] = {3,4};
        hsize_t maxdims[2] = {H5S_UNLIMITED, H5S_UNLIMITED};
        H5::DataSpace dataspace(2, dims, maxdims);

        // Assigning chunking
        H5::DSetCreatPropList props;
        hsize_t chunk_dims[2] = {2,4}; // chunk size for each dimension
        props.setChunk(2, chunk_dims);

        // Creating dataset of integer type
        H5::DataSet dataset = file.createDataSet(GROUP_NAME 
        + "/" + DATASET_NAME, H5::PredType::NATIVE_INT, dataspace, props);

        /*
            Some of the existing HDF5 types are:
            - Integer: H5::PredType::NATIVE_INT
            - Float: H5::PredType::NATIVE_FLOAT
            - Double: H5::PredType::NATIVE_DOUBLE
            - String: H5::StrType(PredType::C_S1, H5T_VARIABLE)
        */

        // Writing metadata /////////////////////////////////////////

        // Writing file metadata
        std::string caption = "This is the file caption";
        int label = 0;
        
        // String type atribute
        file.createAttribute("Caption", H5::StrType(H5::PredType::C_S1,
        H5T_VARIABLE), H5::DataSpace()).write(H5::StrType(
        H5::PredType::C_S1,H5T_VARIABLE), &caption);
        
        // Integer type atribute
        file.createAttribute("Label", H5::PredType::NATIVE_INT, 
        H5::DataSpace()).write(H5::PredType::NATIVE_INT, &label);


        // Writing group metadata
        std::string group_caption = "This is the group caption";
        group.createAttribute("Caption", H5::StrType(H5::PredType::C_S1,
        H5T_VARIABLE), H5::DataSpace()).write(H5::StrType(
        H5::PredType::C_S1,H5T_VARIABLE), &group_caption);

        // Writing dataset metadata
        std::string dataset_caption = "This is the dataset caption";
        dataset.createAttribute("Caption", H5::StrType(H5::PredType::C_S1,
        H5T_VARIABLE), H5::DataSpace()).write(H5::StrType(
        H5::PredType::C_S1,H5T_VARIABLE), &dataset_caption);
        
        // Writing data /////////////////////////////////////////

        int data[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
        dataset.write(data, H5::PredType::NATIVE_INT);

        // Increasing number of rows ///////////////////////////

        // Extending the  dimensions of the dataset
        hsize_t new_dims[2] = {5, 4};
        dataset.extend(new_dims);

        // New data
        int data2[2][4] = {{13, 14, 15, 16}, {17, 18, 19, 20}};

        // Selecting a part of the dataset to write the new data
        H5::DataSpace fspace = dataset.getSpace();
        hsize_t offset[2] = {3, 0}; // Starting point for writing
        hsize_t size[2] = {2, 4};   // Size of the data to write
        fspace.selectHyperslab(H5S_SELECT_SET, size, offset);

        // Creating space in memory
        H5::DataSpace mspace(2, size);

        // Writing new data
        dataset.write(data2, H5::PredType::NATIVE_INT, mspace, fspace);
        
        std::cout << "HDF5 file successfully created" << std::endl;
    } catch (H5::Exception &error) {
        error.printErrorStack();
        return -1;
    }

    return 0;
}
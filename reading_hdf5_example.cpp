#include <H5Cpp.h>
#include <iostream>
#include <string>
#include <vector>

const std::string FILE_NAME("data.h5");
const std::string GROUP_NAME("my_group");
const std::string DATASET_NAME("my_dataset");

int main() {
    try {
        // Opening the file in read-only mode
        H5::H5File file(FILE_NAME, H5F_ACC_RDONLY);

        // Opening the dataset
        H5::DataSet dataset = file.openDataSet(GROUP_NAME + "/" + DATASET_NAME);

        // Getting the dataspace of the dataset
        H5::DataSpace dataspace = dataset.getSpace();

        // Getting the dimensions of the dataset
        int ndims = dataspace.getSimpleExtentNdims();
        hsize_t dims[ndims];
        dataspace.getSimpleExtentDims(dims, NULL);

        std::vector<int> data(dims[0] * dims[1]);

        // Reading the data from the dataset
        dataset.read(data.data(), H5::PredType::NATIVE_INT);

        // Printing the first 10 rows of the dataset
        int limit = std::min(static_cast<int>(dims[0]), 10);
        for (size_t i = 0; i < limit; i++) {
            for (size_t j = 0; j < dims[1]; j++) {
                std::cout << data[i * dims[1] + j] << " ";
            }
            std::cout << std::endl;
        }

    } catch (H5::Exception &error) {
        error.printErrorStack();
        return -1;
    }

    return 0;
}

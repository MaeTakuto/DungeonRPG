#include "../../dxlib_ext/dxlib_ext.h"
#include "csv.h"


ResourceData::ResourceData(std::string csv_path) {

	csv_path_ = csv_path;

	csv_data_ = tnl::LoadCsv(csv_path_);

}
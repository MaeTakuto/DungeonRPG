#pragma once


class ResourceData {
public:
	ResourceData(std::string csv_path_);

	std::vector< std::vector<tnl::CsvCell> > getCsvData() { return csv_data_; }

private:
	std::string csv_path_;

	std::vector< std::vector<tnl::CsvCell> > csv_data_;

};
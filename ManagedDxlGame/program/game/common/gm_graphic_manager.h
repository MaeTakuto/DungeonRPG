#pragma once
#include <string>
#include <unordered_map>


// 画像データの管理するをするクラス
class GraphicManager {
public:
	static GraphicManager* GetInstance();					// インスタンスを返す。
	static void Destroy();									// インスタンスの削除。

	int loadGraph(const std::string& gpc_hdl_path);			// 画像のロード、画像のアドレスを渡す。
	void deleteGraph(const std::string& gpc_hdl_path);		// 画像の削除
 
private:
	GraphicManager();
	~GraphicManager();

	std::unordered_map< std::string, int > gpc_hdl_container_;	// 画像データの格納

};
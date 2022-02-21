#include"compress.h"
/*
功能：利用octree进行点云压缩和解压
*/
extern "C" __declspec(dllexport) int compress_cloud_point()
{
	// 加载点云
	pcl::PointCloud<pcl::PointXYZ> sourceCloud;
	pcl::PCDReader reader;
	if (pcl::io::loadPCDFile("D:\\Python代码\\cloud_point\\Data\\transition2.pcd", sourceCloud) == -1)
	{
		PCL_ERROR("Failed to load PCDFile!");
		return -1;
	}

	// 是否查看压缩信息
	bool showStatistics = true;
	//打印压缩前从文件中读取的点云
	std::cout << "before compress:" << std::endl;
	for (std::size_t i = 0; i < sourceCloud.points.size(); ++i)
	{
		std::cout << "x=" << sourceCloud.points[i].x << "\t" << "y=" << sourceCloud.points[i].y << "\t" << "z=" << sourceCloud.points[i].z << std::endl;
	}
	// 配置文件，如果想看配置文件的详细内容，可以参考: /io/include/pcl/compression/compression_profiles.h
	//分辨率5立方毫米，压缩完之后有颜色，快速在线编码
	//pcl::io::compression_Profiles_e compressionProfile = pcl::io::MED_RES_ONLINE_COMPRESSION_WITH_COLOR;
	//分辨率1立方厘米，压缩完之后有颜色，快速在线编码
	pcl::io::compression_Profiles_e compressionProfile = pcl::io::LOW_RES_ONLINE_COMPRESSION_WITH_COLOR;

	// 初始化点云压缩器和解压器
	pcl::io::OctreePointCloudCompression<pcl::PointXYZ>* PointCloudEncoder;
	PointCloudEncoder = new pcl::io::OctreePointCloudCompression<pcl::PointXYZ>(compressionProfile, showStatistics);//可输入其他参数
	PointCloudEncoder = new pcl::io::OctreePointCloudCompression<pcl::PointXYZ>(compressionProfile, true, 0.002);


	// 压缩结果stringstream
	std::stringstream compressedData;
	// 输出点云
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloudOut(new pcl::PointCloud<pcl::PointXYZ>());
	// 压缩点云 用压缩器调用实现压缩点云的函数 。
	//第一个参数（sourceCloud.makeShared()）是要压缩的点云，第二个参数（compressedData）是压缩生成的字节流。
	PointCloudEncoder->encodePointCloud(sourceCloud.makeShared(), compressedData);
	std::cout << "after compress,the stringstream:" << endl;
	//此处需要做类型转换
	cout << compressedData.str() << endl;
	// 解压点云 第一个参数为字节流 第二个参数为解压后的点云指针
	PointCloudEncoder->decodePointCloud(compressedData, cloudOut);

	//打印解压缩后的点云坐标
	std::cout << "after decode ,the point_cloud:";
	for (size_t i = 0; i < cloudOut->points.size(); ++i)
	{

		std::cout << "x=" << cloudOut->points[i].x << "\t" << "y=" << cloudOut->points[i].y << "\t" << "z=" << cloudOut->points[i].z << std::endl;
	}
	//显示点云
	/*pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
	viewer.showCloud(cloudOut);
	while (!viewer.wasStopped())
	{
	}
	std::system("pause");*/
	return 0;
}

extern "C" __declspec(dllexport) void testCtypes()
{
	printf("just so so\n", CP_UTF8);
}

extern "C" __declspec(dllexport) void testCtypesNumber(int x, float y, bool isNum)
{
	printf("print the three Number :%d,%f,%d\n", x, y, isNum);
	if (isNum == TRUE)
	{
		printf("True");
	}
	else
	{
		printf("False");
	}

}



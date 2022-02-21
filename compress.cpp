#include"compress.h"
/*
���ܣ�����octree���е���ѹ���ͽ�ѹ
*/
extern "C" __declspec(dllexport) int compress_cloud_point()
{
	// ���ص���
	pcl::PointCloud<pcl::PointXYZ> sourceCloud;
	pcl::PCDReader reader;
	if (pcl::io::loadPCDFile("D:\\Python����\\cloud_point\\Data\\transition2.pcd", sourceCloud) == -1)
	{
		PCL_ERROR("Failed to load PCDFile!");
		return -1;
	}

	// �Ƿ�鿴ѹ����Ϣ
	bool showStatistics = true;
	//��ӡѹ��ǰ���ļ��ж�ȡ�ĵ���
	std::cout << "before compress:" << std::endl;
	for (std::size_t i = 0; i < sourceCloud.points.size(); ++i)
	{
		std::cout << "x=" << sourceCloud.points[i].x << "\t" << "y=" << sourceCloud.points[i].y << "\t" << "z=" << sourceCloud.points[i].z << std::endl;
	}
	// �����ļ�������뿴�����ļ�����ϸ���ݣ����Բο�: /io/include/pcl/compression/compression_profiles.h
	//�ֱ���5�������ף�ѹ����֮������ɫ���������߱���
	//pcl::io::compression_Profiles_e compressionProfile = pcl::io::MED_RES_ONLINE_COMPRESSION_WITH_COLOR;
	//�ֱ���1�������ף�ѹ����֮������ɫ���������߱���
	pcl::io::compression_Profiles_e compressionProfile = pcl::io::LOW_RES_ONLINE_COMPRESSION_WITH_COLOR;

	// ��ʼ������ѹ�����ͽ�ѹ��
	pcl::io::OctreePointCloudCompression<pcl::PointXYZ>* PointCloudEncoder;
	PointCloudEncoder = new pcl::io::OctreePointCloudCompression<pcl::PointXYZ>(compressionProfile, showStatistics);//��������������
	PointCloudEncoder = new pcl::io::OctreePointCloudCompression<pcl::PointXYZ>(compressionProfile, true, 0.002);


	// ѹ�����stringstream
	std::stringstream compressedData;
	// �������
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloudOut(new pcl::PointCloud<pcl::PointXYZ>());
	// ѹ������ ��ѹ��������ʵ��ѹ�����Ƶĺ��� ��
	//��һ��������sourceCloud.makeShared()����Ҫѹ���ĵ��ƣ��ڶ���������compressedData����ѹ�����ɵ��ֽ�����
	PointCloudEncoder->encodePointCloud(sourceCloud.makeShared(), compressedData);
	std::cout << "after compress,the stringstream:" << endl;
	//�˴���Ҫ������ת��
	cout << compressedData.str() << endl;
	// ��ѹ���� ��һ������Ϊ�ֽ��� �ڶ�������Ϊ��ѹ��ĵ���ָ��
	PointCloudEncoder->decodePointCloud(compressedData, cloudOut);

	//��ӡ��ѹ����ĵ�������
	std::cout << "after decode ,the point_cloud:";
	for (size_t i = 0; i < cloudOut->points.size(); ++i)
	{

		std::cout << "x=" << cloudOut->points[i].x << "\t" << "y=" << cloudOut->points[i].y << "\t" << "z=" << cloudOut->points[i].z << std::endl;
	}
	//��ʾ����
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



#pragma once
template<typename Object>
struct TreeNode {
	Object element;
	TreeNode* firstChild;
	TreeNode* nextSibling;
};
#if 0
//�г��ּ��ļ�ϵͳ�е�Ŀ¼��α��������
void FileSystem::listAll(int depth = 0)const
{
	printName(depth);   // Print the name of the object
	if (isDirectory())
		for each file c in this directory(for each child)
			c.listAll(depth + 1);
}

//����һ��Ŀ¼��С��α��������
int FileSystem::Size() const
{
	int totalSize = sizeOfThisFile();
	if (isDirectory())
		for each file c in this directory(for each child)
			totalSize += c.size();
	return totalSize;
}
#endif
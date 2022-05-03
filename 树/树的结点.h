#pragma once
template<typename Object>
struct TreeNode {
	Object element;
	TreeNode* firstChild;
	TreeNode* nextSibling;
};
#if 0
//列出分级文件系统中的目录的伪代码历程
void FileSystem::listAll(int depth = 0)const
{
	printName(depth);   // Print the name of the object
	if (isDirectory())
		for each file c in this directory(for each child)
			c.listAll(depth + 1);
}

//计算一个目录大小的伪代码历程
int FileSystem::Size() const
{
	int totalSize = sizeOfThisFile();
	if (isDirectory())
		for each file c in this directory(for each child)
			totalSize += c.size();
	return totalSize;
}
#endif
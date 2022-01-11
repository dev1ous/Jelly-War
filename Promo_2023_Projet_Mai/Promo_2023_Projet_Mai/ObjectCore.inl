template<typename T>
inline void ObjectCore::NewCreation(T value)
{
	ObjectCore* current(from->Main.get());

	for (int i = 0; i < from->operator_path.size(); i++)
	{
		if (i == from->operator_path.size() - 1) // value
		{
			current->operator[](from->operator_path[i]);
			from->operator_path.clear();
			*current << value;
		}
		else // objects
		{
			if (current->Values.find(from->operator_path[i]) != current->Values.end())
			{
				current->Values.erase(current->Values.find(from->operator_path[i]));
			}

			current->Objects.insert({ from->operator_path[i], ObjectCore() });
			current->Objects[from->operator_path[i]].from = from;
			current->Objects[from->operator_path[i]].parent = current;
			current = &current->Objects[from->operator_path[i]];
		}
	}

}
class Weather{
	private:
	   	int Wind_start, Wind_end, Sea_start, alfa_start, alfa_end, counter;
	public:	
		float Wind_now, Sea_now, alfa_now;
		Weather();
		void refresh();
};

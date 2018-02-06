

class Block{

	private:
		int color = 0;
		int * coordinates;
		bool block_empty = true;


	public:
		Block(){
			coordinates = new int[2];

		}
		~Block(){

			delete coordinates;

		}

		int getColor(){return color;}
		
		void setCoordinates(int Y, int X ){
			coordinates[0]= Y;
			coordinates[1]= X;
		}
		int get_Y(){
			return coordinates[0];
			
		}

		int get_X(){
			return coordinates[1];
			
		}

		bool isEmpty(){

			return block_empty;
		}

		void setState(bool etat){
			block_empty = etat;
		}








};
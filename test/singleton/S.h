#ifndef _SS__H_
#define _SS__H_

class S
{
	public:
		static S& getInstance()
		{
			static S    instance; // Guaranteed to be destroyed.
			// Instantiated on first use.
			return instance;
		}
	private:
		S() {};                   // Constructor? (the {} brackets) are needed here.
		// Dont forget to declare these two. You want to make sure they
		// are unaccessable otherwise you may accidently get copies of
		// your singleton appearing.
		S(S const&);              // Don't Implement
		void operator=(S const&); // Don't implement
};

#endif

#include "args.h"


Args::Args(int argc, char** argv)
{
	Param* param;

	// if we have less than two args then it doesn't make
	// any sense to parse the command line
	if( argc < 2 )
	{
		return;
	}

	// the command must always be the first parameter passed to the app
	param = new Param("command", argv[1]);

	mParams.push_back( param );


	// iterate through each argument
	// if the argument contains an = sign then split it into a name value pair
	// if it doesn't contain an equal sign then it should be the first argument only
	// in which case the name for the argument is "command" and the passed value is 
	// the value for this command

	for(int i = 2; i < argc; i++)
	{
		std::string str;
		int pos;

		str = argv[i];
		
		pos = str.find("=");
		
		if(pos == str.npos)
		{
			// equal sign not found
			// check for presence of a question mark
			#ifdef osx
				pos = str.find("-h");
			#endif
			#ifdef win32
				pos = str.find("?");
			#endif
			if( pos != str.npos )
			{
				param = new Param("?", "?");
				mParams.push_back( param );
			}
		}
		else
		{
			#ifdef osx
				param = new Param(str.substr(0, pos), str.substr(pos+1, (str.length() - pos+3)));
			#else
				param = new Param(str.substr(0, pos), str.substr(pos+1));			
			#endif
			mParams.push_back( param );
		}
	}
}

int Args::Count()
{
	return(mParams.size());
}

bool Args::Exists(std::string key)
{
	Param* param;

	for( int i = 0; i < this->Count(); i++)
	{
		param = mParams[i];

		if( key.compare( param->Name() ) == 0 )
		{
			return( true );	
		}
	}

	return( false );
}

std::string Args::Key(int index)
{
	//determine if the specified index value 
	//falls within the accetable values for the
	// vector
	if( index > this->Count() )
	{
		return( 0 );
	}

	Param* param;

	// retrieve the item that is associated with this index and return the 
	// key value for this item
	param = mParams[index];

	return( param->Name() );
	
}


std::string Args::Val(int index)
{
	// determine if the specified index value
	// falls within the acceptable values for the
	// vector
	if( index > this->Count() )
	{
		return( "" );
	}

	Param* param;

	// retrieve the item that is associated with this index and return the key value for
	// this item
	param = mParams[index];

	return( param->Value() );
}

std::string Args::Val(std::string key)
{
	Param* param;

	for( int i = 0; i < this->Count(); i++)
	{
		param = mParams[i];

		if( key.compare( param->Name() ) == 0 )
		{
			return( param->Value() );	
		}
	}

	return( "" );
}

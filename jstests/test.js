
const assert = require("assert");

const jswd = require("jswd");

const dbgeng = require("dbgeng");

const fmt = require("fmt");

const typing = require("typing");



function sizeOfPrimitive(type)
{
	switch ( type.toLowerCase() )
	{
		case 'int':
		case 'uint':
		{
			return 4;
		}

		case 'int8':
		case 'uint8':
		case 'byte':
		case 'char':
		case 'uchar':
		case 'signed char':
		case 'unsigned char':
		{
			return 1;
		}

		case 'int16':
		case 'uint16':
		case 'short':
		case 'ushort':
		case 'word':
		case 'unsigned short':
		{
			return 2;
		}

		case 'int32':
		case 'uint32':
		case 'dword':
		case 'dword32':
		case 'unsigned int':
		{
			return 4;
		}

		case 'int64':
		case 'uint64':
		case 'dword64':
		case 'qword':
		{
			return 8;
		}

		case 'float':
		case 'float32':
		{
			return 4;
		}

		case 'double':
		case 'float64':
		{
			return 8;
		}

		default:
		{
			throw new Error( fmt.sprintf("Unsupported primitive type: %s" , type) );
		}
	}
}



class Struct
{
	constructor( name , align = 1 )
	{
		this.name = name;

		this.align = align;

		this.fields = [];

		this.offset = 0;
	}

	addField(name , type )
	{
		let field = {
			'name' : name,
			'type' : type
		};

		if ( typing.isString(type) )
		{
			field.size = sizeOfPrimitive(type);
		}
		else if ( typing.isFunction(type.sizeOf) )
		{
			field.size = type.sizeOf();
		}
		else
		{
			throw new Error( fmt.sprintf("Invalid field type: %s}" , type  ) );
		}

		field.offset = this.alignField(field.size);

		this.fields.push(field);

		return this;
	}

	alignField( size )
	{
		if ( 0 === this.fields.length )
		{
			return 0;
		}

		let offset = this.sizeOf();

		if ( 0 !== (offset % this.align ) )
		{
			if ( 0 !== ( size % this.align ) )
			{
				offset += this.align - ( offset % this.align);
			}
		}

		return offset;
	}

	sizeOf()
	{
		if ( 0 === this.fields.length )
		{
			return 0;
		}

		const lastField = this.fields[this.fields.length - 1];

		return lastField.offset + lastField.size;
	}

	fieldOffset(name)
	{
		let i  = 0;

		for ( i = 0; i < this.fields.length; i++ )
		{
			if ( name === this.fields[i].name )
			{
				return this.fields[i].offset;
			}
		}

		throw new Error( fmt.sprintf( "Unknown field: %s" , name ) );
	}

	fieldSize(name)
	{
		let i  = 0;

		for ( i = 0; i < this.fields.length; i++ )
		{
			if ( name === this.fields[i].name )
			{
				return this.fields[i].size;
			}
		}

		throw new Error( fmt.sprintf( "Unknown field: %s" , name ) );
	}
}


function main(argv)
{
	//debugger;
	
	let UNICODE_STRING = new Struct('UNICODE_STRING'  );

	UNICODE_STRING.addField('Length' , 'uint16');

	UNICODE_STRING.addField('MaximumLength' , 'uint16');

	UNICODE_STRING.addField('__aligned' , 'uint32');

	UNICODE_STRING.addField('Buffer' , 'uint64');

	fmt.printf("fieldOffset(UNICODE_STRING , Length) = %d\n" , UNICODE_STRING.fieldOffset('Length') );

	fmt.printf("fieldOffset(UNICODE_STRING , MaximumLength) = %d\n" , UNICODE_STRING.fieldOffset('MaximumLength') );

	fmt.printf("fieldOffset(UNICODE_STRING , Buffer) = %d\n" , UNICODE_STRING.fieldOffset('Buffer') );

	fmt.printf("sizeof(UNICODE_STRING) = %d\n" , UNICODE_STRING.sizeOf() );

    return 0;
}
exports.main = main;


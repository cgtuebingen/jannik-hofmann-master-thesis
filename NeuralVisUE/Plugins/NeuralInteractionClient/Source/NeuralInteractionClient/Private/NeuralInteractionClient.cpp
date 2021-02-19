// Copyright Epic Games, Inc. All Rights Reserved.
// Code adapted from
// https://www.boost.org/doc/libs/1_75_0/libs/beast/example/websocket/client/async/websocket_client_async.cpp

#include "INeuralInteractionClient.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

//#define LOCTEXT_NAMESPACE "FNeuralInteractionClient"
THIRD_PARTY_INCLUDES_START
#pragma push_macro("check")
#undef check
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <boost/thread/thread.hpp>
#include <msgpack.hpp>
#pragma pop_macro("check")
THIRD_PARTY_INCLUDES_END

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

DECLARE_LOG_CATEGORY_EXTERN(NeuralInteractionClient, Log, All);
DEFINE_LOG_CATEGORY(NeuralInteractionClient);

// Report a failure
void
fail(beast::error_code ec, char const* what)
{
	//std::cerr << what << ": " << ec.message() << "\n";
	//UE_LOG(LogTemp, Warning, TEXT(what));
}

// Report debug text
void
debug(char const* what, bool forceprinterror = false)
{
	if (forceprinterror) {
		//std::cout << "ERROR! " << what << "\n\n";
		//print("ERROR! " + what));
		;//UE_LOG(LogTemp, Warning, TEXT("ERROR!" + what));
	} else {
		//std::cout << "\t\t\t\t\t\t\t" << what << "\n";
		;
	}
}

// Report debug text
void
print(std::string what)
{
	//FString tmp = what.c_str()
	//UE_LOG(LogTemp, Log, TEXT(tmp));
}

// Sends a WebSocket message and prints the response
class session : public std::enable_shared_from_this<session>
{
	tcp::resolver resolver_;
	websocket::stream<beast::tcp_stream> ws_;
	beast::flat_buffer buffer_;
	std::string host_;
	std::string text_;
	FReadResponse sessionCallback;
	bool sessionCallbackSet = false;
	FEndOfConnection sessionCallbackEndOfConnection;
	FEndOfReponse sessionCallbackEndOfReponse;
	FParseError sessionCallbackParseError;
	FStartOrEndOfMap sessionCallbackStartOrEndOfMap;
	FStartOrEndOfArray sessionCallbackStartOrEndOfArray;
	FFoundAtomNil sessionCallbackFoundAtomNil;
	FFoundAtomString sessionCallbackFoundAtomString;
	FFoundAtomBinary sessionCallbackFoundAtomBinary;
	FFoundAtomExternal sessionCallbackFoundAtomExternal;
	FFoundAtomBoolean sessionCallbackFoundAtomBoolean;
	FFoundAtomInteger sessionCallbackFoundAtomInteger;
	FFoundAtomInteger64 sessionCallbackFoundAtomInteger64;
	FFoundAtomFloat sessionCallbackFoundAtomFloat;
	bool sessionCallbacksCompletelySet = false;

public:
	// Resolver and socket require an io_context
	explicit
		session(net::io_context& ioc)
		: resolver_(net::make_strand(ioc))
		, ws_(net::make_strand(ioc))
	{
	}

	// Start the asynchronous operation
	void
		run(
			char const* host,
			char const* port,
			char const* text)
	{
		debug("run called");
		// Save these for later
		host_ = host;
		text_ = text;

		// Look up the domain name
		resolver_.async_resolve(
			host,
			port,
			beast::bind_front_handler(
				&session::on_resolve,
				shared_from_this()));
	}

	// Start the asynchronous operation
	void
		runAdvanced(
			const FReadResponse& Callback,
			char const* host,
			char const* port,
			char const* text)
	{
		debug("run called");
		// Save these for later
		host_ = host;
		text_ = text;
		sessionCallback = Callback;
		sessionCallbackSet = true;

		//sessionCallback.Execute(TEXT("Delegate was just called from sessionCallback."));

		// Look up the domain name
		resolver_.async_resolve(
			host,
			port,
			beast::bind_front_handler(
				&session::on_resolve,
				shared_from_this()));
	}

	// Start the asynchronous operation
	void
		runWithAllDelegates(
			const FEndOfConnection& CallbackEndOfConnection,
			const FEndOfReponse& CallbackEndOfReponse,
			const FParseError& CallbackParseError,
			const FStartOrEndOfMap& CallbackStartOrEndOfMap,
			const FStartOrEndOfArray& CallbackStartOrEndOfArray,
			const FFoundAtomNil& CallbackFoundAtomNil,
			const FFoundAtomString& CallbackFoundAtomString,
			const FFoundAtomBinary& CallbackFoundAtomBinary,
			const FFoundAtomExternal& CallbackFoundAtomExternal,
			const FFoundAtomBoolean& CallbackFoundAtomBoolean,
			const FFoundAtomInteger& CallbackFoundAtomInteger,
			const FFoundAtomInteger64& CallbackFoundAtomInteger64,
			const FFoundAtomFloat& CallbackFoundAtomFloat,
			char const* host,
			char const* port,
			char const* text)
	{
		debug("run called");
		// Save these for later
		host_ = host;
		text_ = text;
		
		sessionCallbackEndOfConnection = CallbackEndOfConnection;
		sessionCallbackEndOfReponse = CallbackEndOfReponse;
		sessionCallbackParseError = CallbackParseError;
		sessionCallbackStartOrEndOfMap = CallbackStartOrEndOfMap;
		sessionCallbackStartOrEndOfArray = CallbackStartOrEndOfArray;
		sessionCallbackFoundAtomNil = CallbackFoundAtomNil;
		sessionCallbackFoundAtomString = CallbackFoundAtomString;
		sessionCallbackFoundAtomBinary = CallbackFoundAtomBinary;
		sessionCallbackFoundAtomExternal = CallbackFoundAtomExternal;
		sessionCallbackFoundAtomBoolean = CallbackFoundAtomBoolean;
		sessionCallbackFoundAtomInteger = CallbackFoundAtomInteger;
		sessionCallbackFoundAtomInteger64 = CallbackFoundAtomInteger64;
		sessionCallbackFoundAtomFloat = CallbackFoundAtomFloat;
		sessionCallbacksCompletelySet = true;

		// Look up the domain name
		resolver_.async_resolve(
			host,
			port,
			beast::bind_front_handler(
				&session::on_resolve,
				shared_from_this()));
	}

	void
		on_resolve(
			beast::error_code ec,
			tcp::resolver::results_type results)
	{
		debug("on resolve called");
		if (ec)
			return fail(ec, "resolve");

		// Set the timeout for the operation
		beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(30));

		// Make the connection on the IP address we get from a lookup
		beast::get_lowest_layer(ws_).async_connect(
			results,
			beast::bind_front_handler(
				&session::on_connect,
				shared_from_this()));
	}

	void
		on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep)
	{
		debug("on connect called");
		if (ec)
			return fail(ec, "connect");

		// Turn off the timeout on the tcp_stream, because
		// the websocket stream has its own timeout system.
		beast::get_lowest_layer(ws_).expires_never();

		// Set suggested timeout settings for the websocket
		ws_.set_option(
			websocket::stream_base::timeout::suggested(
				beast::role_type::client));

		// Set a decorator to change the User-Agent of the handshake
		ws_.set_option(websocket::stream_base::decorator(
			[](websocket::request_type& req)
		{
			req.set(http::field::user_agent,
				std::string(BOOST_BEAST_VERSION_STRING) +
				" websocket-client-async");
		}));

		// Update the host_ string. This will provide the value of the
		// Host HTTP header during the WebSocket handshake.
		// See https://tools.ietf.org/html/rfc7230#section-5.4
		host_ += ':' + std::to_string(ep.port());

		// Perform the websocket handshake
		ws_.async_handshake(host_, "/",
			beast::bind_front_handler(
				&session::on_handshake,
				shared_from_this()));
	}

	void
		on_handshake(beast::error_code ec)
	{
		debug("on handshake called");
		if (ec)
			return fail(ec, "handshake");

		// Send the message
		ws_.async_write(
			net::buffer(text_),
			beast::bind_front_handler(
				&session::on_write,
				shared_from_this()));
	}

	void
		on_write(
			beast::error_code ec,
			std::size_t bytes_transferred)
	{
		debug("on write called");
		boost::ignore_unused(bytes_transferred);

		if (ec)
			return fail(ec, "write");

		// Read a message into our buffer
		ws_.async_read(
			buffer_,
			beast::bind_front_handler(
				&session::on_read,
				shared_from_this()));
	}

	void
		on_read(
			beast::error_code ec,
			std::size_t bytes_transferred)
	{
		debug("on read called");
		boost::ignore_unused(bytes_transferred);

		if (ec) {
			if (sessionCallbacksCompletelySet) {
				if (ec.value() == 1) {
					// The WebSocket stream was gracefully closed at both endpoints
					sessionCallbackEndOfConnection.Execute(UTF8_TO_TCHAR(text_.c_str()), false);
				} else if (ec.value() == 10054) {
					// An existing connection was forcibly closed by the remote host
					sessionCallbackEndOfConnection.Execute(UTF8_TO_TCHAR(text_.c_str()), true);
				} else {
					// Any other unidentified error
					sessionCallbackEndOfConnection.Execute(UTF8_TO_TCHAR(text_.c_str()), true);
				}
			}
			return fail(ec, "read");
		}

		std::string response;
		unpackmsgpack();

		buffer_.clear();

		// PATIENT CLIENT / KEEP READING:
		// Read next message into our buffer or check for closed connection
		ws_.async_read(
			buffer_,
			beast::bind_front_handler(
				&session::on_read,
				shared_from_this()));

		// ECHO CLIENT:
		// Send the message
		/*ws_.async_write(
			net::buffer(text_),
			beast::bind_front_handler(
				&session::on_write,
				shared_from_this()));*/


		// ORIGINAL CODE OPTION / IMPATIENT CLIENT:
		// Close the WebSocket connection
		/*ws_.async_close(websocket::close_code::normal,
			beast::bind_front_handler(
				&session::on_close,
				shared_from_this()));*/
	}

	void
		on_close(beast::error_code ec)
	{
		debug("on close called");
		if (ec)
			return fail(ec, "close");

		// If we get here then the connection is closed gracefully
		if (sessionCallbacksCompletelySet) {
			sessionCallbackEndOfConnection.Execute(UTF8_TO_TCHAR(text_.c_str()), false);
		}

		// The make_printable() function helps print a ConstBufferSequence
		//std::cout << beast::make_printable(buffer_.data()) << std::endl;
		//print(beast::make_printable(buffer_.data()));
	}

	void unpackmsgpack() {
		// original command is stored in: std::string text_
		//std::cout << text_ << ": ";
		//print(text_ + ": ");

		// response is in: buffer_

		std::string response = beast::buffers_to_string(buffer_.data());
		msgpack::sbuffer buffer;
		buffer.write(&response[0], buffer_.size());

		// deserializes these objects using msgpack::unpacker.
		msgpack::unpacker unpacker;

		// feeds the buffer.
		unpacker.reserve_buffer(buffer.size());
		memcpy(unpacker.buffer(), buffer.data(), buffer.size());
		unpacker.buffer_consumed(buffer.size());

		// deserialize and print received packed at once:
		/*msgpack::object_handle oh;
		oh = msgpack::unpack(response.data(), response.size());
		std::cout << oh.get() << std::endl;*/
		// alternative:
		/*while (unpacker.next(oh)) {
			std::cout << oh.get() << std::endl;
		}*/
		//std::cout << std::endl;
		print("\n");

		// apply visitor, unpack everything
		{
			msgpack_visitor visitor;
			if (sessionCallbackSet) {
				visitor.setCallbackFunction(sessionCallback);
			}
			if (sessionCallbacksCompletelySet) {
				visitor.setCallbackFunctionsCompletely(
					sessionCallbackEndOfConnection,
					sessionCallbackEndOfReponse,
					sessionCallbackParseError,
					sessionCallbackStartOrEndOfMap,
					sessionCallbackStartOrEndOfArray,
					sessionCallbackFoundAtomNil,
					sessionCallbackFoundAtomString,
					sessionCallbackFoundAtomBinary,
					sessionCallbackFoundAtomExternal,
					sessionCallbackFoundAtomBoolean,
					sessionCallbackFoundAtomInteger,
					sessionCallbackFoundAtomInteger64,
					sessionCallbackFoundAtomFloat
				);
				visitor.setOriginalCommand(text_);
			}
			msgpack::parse(response.data(), response.size(), visitor);
			/*if (sessionCallbacksCompletelySet) {
				sessionCallbackEndOfReponse.Execute(originalCommand, FfirstString);
			}*/
			//std::cout << std::endl;
			print("\n");
		}
	}

	static void createLayer(int layerNumber, int size_x, int size_y, int size_z, std::string name) {
		//std::cout << std::endl << "Creating layer number " << layerNumber << " with name " <<
		//	name << " of size " << size_x << ", " << size_y << ", " << size_z << ".";
		/*std::string strr;
		strr << "Creating layer number " << layerNumber << " with name " <<
			name << " of size " << size_x << ", " << size_y << ", " << size_z << ".";
		print(strr);*/
	}

	struct msgpack_visitor : msgpack::null_visitor {
		int depth = 0;
		const std::string indent = "  ";
		const std::string indentBeforeEveryLine = "    ";
		bool startWithNewLine = false;
		const bool showArrayBrackets = false;
		bool processing_map_key = false;
		bool processing_map_value = false;
		std::string printThisAfterNextWhitespace = "";
		std::string firstString = "";
		FString FfirstString = "";
		int tmpArrayLength;
		int tmpX, tmpY, tmpZ, tmpCount;
		bool tmpReading = false;
		std::string tmpStr = "";
		FReadResponse visitorCallback;
		bool visitorCallbackSet = false;
		FString originalCommand = "";
		std::string arrayPosition = "";
		FString FarrayPosition = "";

		FEndOfConnection visitorCallbackEndOfConnection;
		FEndOfReponse visitorCallbackEndOfReponse;
		FParseError visitorCallbackParseError;
		FStartOrEndOfMap visitorCallbackStartOrEndOfMap;
		FStartOrEndOfArray visitorCallbackStartOrEndOfArray;
		FFoundAtomNil visitorCallbackFoundAtomNil;
		FFoundAtomString visitorCallbackFoundAtomString;
		FFoundAtomBinary visitorCallbackFoundAtomBinary;
		FFoundAtomExternal visitorCallbackFoundAtomExternal;
		FFoundAtomBoolean visitorCallbackFoundAtomBoolean;
		FFoundAtomInteger visitorCallbackFoundAtomInteger;
		FFoundAtomInteger64 visitorCallbackFoundAtomInteger64;
		FFoundAtomFloat visitorCallbackFoundAtomFloat;
		bool visitorCallbacksCompletelySet = false;

		void setCallbackFunction(const FReadResponse& Callback) {
			visitorCallback = Callback;
			visitorCallbackSet = true;
		}

		void setCallbackFunctionsCompletely(
			const FEndOfConnection& CallbackEndOfConnection,
			const FEndOfReponse& CallbackEndOfReponse,
			const FParseError& CallbackParseError,
			const FStartOrEndOfMap& CallbackStartOrEndOfMap,
			const FStartOrEndOfArray& CallbackStartOrEndOfArray,
			const FFoundAtomNil& CallbackFoundAtomNil,
			const FFoundAtomString& CallbackFoundAtomString,
			const FFoundAtomBinary& CallbackFoundAtomBinary,
			const FFoundAtomExternal& CallbackFoundAtomExternal,
			const FFoundAtomBoolean& CallbackFoundAtomBoolean,
			const FFoundAtomInteger& CallbackFoundAtomInteger,
			const FFoundAtomInteger64& CallbackFoundAtomInteger64,
			const FFoundAtomFloat& CallbackFoundAtomFloat
		) {
			visitorCallbackEndOfConnection = CallbackEndOfConnection;
			visitorCallbackEndOfReponse = CallbackEndOfReponse;
			visitorCallbackParseError = CallbackParseError;
			visitorCallbackStartOrEndOfMap = CallbackStartOrEndOfMap;
			visitorCallbackStartOrEndOfArray = CallbackStartOrEndOfArray;
			visitorCallbackFoundAtomNil = CallbackFoundAtomNil;
			visitorCallbackFoundAtomString = CallbackFoundAtomString;
			visitorCallbackFoundAtomBinary = CallbackFoundAtomBinary;
			visitorCallbackFoundAtomExternal = CallbackFoundAtomExternal;
			visitorCallbackFoundAtomBoolean = CallbackFoundAtomBoolean;
			visitorCallbackFoundAtomInteger = CallbackFoundAtomInteger;
			visitorCallbackFoundAtomInteger64 = CallbackFoundAtomInteger64;
			visitorCallbackFoundAtomFloat = CallbackFoundAtomFloat;
			visitorCallbacksCompletelySet = true;
		}

		void setOriginalCommand(std::string command) {
			originalCommand = UTF8_TO_TCHAR(command.c_str());
		}

		void enterArray() {
			if (arrayPosition == "") {
				arrayPosition = "-1";
			}
			else {
				arrayPosition += ".-1";
			}
			FarrayPosition = UTF8_TO_TCHAR(arrayPosition.c_str());
			//std::cout << "                      Enter: " << arrayPosition;
			depth++;
		}
		void leaveArray() {
			if (arrayPosition.find(".") == std::string::npos) {
				arrayPosition = "";
			}
			else {
				arrayPosition.erase(arrayPosition.rfind("."));
			}
			FarrayPosition = UTF8_TO_TCHAR(arrayPosition.c_str());
			//std::cout << "                      Leave: " << arrayPosition;
			depth--;
		}
		void incrementArrayPosition() {
			if (arrayPosition.find(".") == std::string::npos) {
				int value = atoi(arrayPosition.c_str());
				value++;
				arrayPosition = std::to_string(value);
			}
			else {
				int dotpos = arrayPosition.find_last_of(".");
				std::string parentArrayPos = arrayPosition.substr(0, dotpos);
				int value = atoi(arrayPosition.substr(dotpos+1).c_str());
				value++;
				arrayPosition = parentArrayPos + "." + std::to_string(value);
			}
			FarrayPosition = UTF8_TO_TCHAR(arrayPosition.c_str());
			//std::cout << "                      Incr.: " << arrayPosition;
		}
		void debugPrintArrayPosition() {
			//std::cout << " \033[90m" << "(" << arrayPosition << ")\033[0m";
		}

		void debugvisitor(std::string debugmsg, bool closeArray = false) {
			debugmsg += "\033[0m";
			//return; // to disable debug output
			if (closeArray) {
				if (showArrayBrackets)
					//std::cout << indent << debugmsg;
					print(indent);
			}
			else {
				if (startWithNewLine)
					//std::cout << std::endl; // new line. doing it now for closing arrays
					print("\n");
				//std::cout << indentBeforeEveryLine;
				print(indentBeforeEveryLine);
				for (int i = 0; i < depth; i++) {
					//std::cout << indent;
					print(indent);
				}
				//std::cout << printThisAfterNextWhitespace << debugmsg;
				print(printThisAfterNextWhitespace + debugmsg);
				printThisAfterNextWhitespace = "";
				startWithNewLine = true;
			}
		}

		bool start_map(uint32_t num_kv_pairs) {
			/*std::string debugstr = "map: keys" + indentBeforeEveryLine + indent;
			for (int i = 0; i < depth; i++) {
				debugstr += indent;
			}
			debugstr += "values";
			debugvisitor(debugstr);*/
			debugvisitor("\033[94mmap");
			debugPrintArrayPosition();
			enterArray();
			return true;
		}
		bool start_map_key() {
			incrementArrayPosition();
			enterArray();
			incrementArrayPosition();
			processing_map_key = true;
			//debugvisitor("start map key.");
			//debugvisitor("map key: ");
			return true;
		}
		bool end_map_key() {
			processing_map_key = false;
			//debugvisitor("end map key.");
			return true;
		}
		bool start_map_value() {
			incrementArrayPosition();
			processing_map_value = true;
			startWithNewLine = false;
			//debugvisitor("start map value.");
			return true;
		}
		bool end_map_value() {
			processing_map_value = false;
			//debugvisitor("end map value.");
			leaveArray();
			return true;
		}
		bool end_map() {
			leaveArray();
			//debugvisitor("end map.");
			return true;
		}

		bool start_array(uint32_t size) {
			debugvisitor("\033[94marray (size " + std::to_string(size) + ")" +
				(showArrayBrackets ? indent + "[" : ""));
			debugPrintArrayPosition();
			if (firstString == "TF STRUCTURE") {
				if (depth == 1) { // initializations
					tmpArrayLength = size; // storing number of layers
					tmpCount = 0;
					tmpX = 0; tmpY = 0; tmpZ = 0;
				}
			}
			enterArray();
			return true;
		}
		bool start_array_item() {
			//debugvisitor("start array item.");
			incrementArrayPosition();
			//printThisAfterNextWhitespace = "\b\b- ";
			return true;
		}
		bool end_array_item() {
			//debugvisitor("end array item.");
			return true;
		}
		bool end_array() {
			if (firstString == "TF STRUCTURE") {
				if (depth == 4) {
					// finished dimensions array of layer # tmpCount
					if (tmpX == 0) tmpX = 1;
					if (tmpY == 0) tmpY = 1;
					if (tmpZ == 0) tmpZ = 1;
					createLayer(tmpCount, tmpX, tmpY, tmpZ, tmpStr);
					tmpX = 0; tmpY = 0; tmpZ = 0;
					tmpStr = "";
					tmpCount++;
				}
			}
			leaveArray();
			debugvisitor("\033[94m]", true);
			return true;
		}

		bool visit_nil() {
			debugvisitor("\033[35mnil.");
			debugPrintArrayPosition();
			if (visitorCallbacksCompletelySet) {
				visitorCallbackFoundAtomNil.Execute(originalCommand, FfirstString, FarrayPosition);
			}
			return true;
		}
		bool visit_boolean(bool v) {
			if (v)
				debugvisitor("\033[91mtrue");
			else
				debugvisitor("\033[91mfalse");
			debugPrintArrayPosition();
			if (visitorCallbacksCompletelySet) {
				visitorCallbackFoundAtomBoolean.Execute(originalCommand, FfirstString, FarrayPosition, v);
			}
			return true;
		}
		bool visit_positive_integer(uint64_t v) {
			debugvisitor("int: \033[96m" + std::to_string(v));
			if (firstString == "TF STRUCTURE") {
				if (depth == 4) {
					if (tmpX == 0) tmpX = v;
					else if (tmpY == 0) tmpY = v;
					else if (tmpZ == 0) tmpZ = v;
					//else std::cout << "Too many dimensions! Value " << v << " of layer " << tmpCount << " cannot be visualized!";
					else ;//print("Too many dimensions! Value " + std::string(v) + " of layer " + std::string(tmpCount) + " cannot be visualized!");
				}
			}
			debugPrintArrayPosition();
			if (visitorCallbacksCompletelySet) {
				visitorCallbackFoundAtomInteger64.Execute(originalCommand, FfirstString, FarrayPosition, v);
			}
			return true;
		}
		bool visit_negative_integer(int64_t v) {
			debugvisitor("neg int: \033[96m" + std::to_string(v));
			debugPrintArrayPosition();
			if (visitorCallbacksCompletelySet) {
				visitorCallbackFoundAtomInteger64.Execute(originalCommand, FfirstString, FarrayPosition, v);
			}
			return true;
		}
		bool visit_float32(float v) {
			debugvisitor("float: \033[92m" + std::to_string(v));
			debugPrintArrayPosition();
			if (visitorCallbacksCompletelySet) {
				visitorCallbackFoundAtomFloat.Execute(originalCommand, FfirstString, FarrayPosition, v);
			}
			return true;
		}
		bool visit_float64(double v) {
			debugvisitor("double: \033[92m" + std::to_string(v));
			debugPrintArrayPosition();
			if (visitorCallbacksCompletelySet) {
				visitorCallbackFoundAtomFloat.Execute(originalCommand, FfirstString, FarrayPosition, v);
			}
			return true;
		}
		bool visit_str(const char* v, uint32_t size) {
			debugvisitor("\"\033[95m" + std::string(v, size) + "\033[0m\"");
			if (firstString == "" && depth == 1) {
				firstString = std::string(v, size);
				FfirstString = UTF8_TO_TCHAR(firstString.c_str());
			} else if (firstString == "TF STRUCTURE") {
				if (depth == 3) {
					if (tmpStr == "")
						tmpStr = std::string(v, size);
				}
			}
			debugPrintArrayPosition();
			if (visitorCallbackSet) {
				FString output(v);
				visitorCallback.Execute(output);
			}
			if (visitorCallbacksCompletelySet) {
				FString output(size, v);
				visitorCallbackFoundAtomString.Execute(originalCommand, FfirstString, FarrayPosition, output);
			}
			return true;
		}
		bool visit_bin(const char* data, uint32_t size) {
			std::string sdata(data, size);
			debugvisitor("binary: \033[93m" + sdata);
			debugPrintArrayPosition();
			if (visitorCallbacksCompletelySet) {
				FString output(size, data);
				visitorCallbackFoundAtomBinary.Execute(originalCommand, FfirstString, FarrayPosition, output);
			}
			return true;
		}
		bool visit_ext(const char* data, uint32_t size) {
			std::string sdata(data, size);
			debugvisitor("ext: \033[33m" + sdata);
			debugPrintArrayPosition();
			if (visitorCallbacksCompletelySet) {
				FString output(size, data);
				visitorCallbackFoundAtomExternal.Execute(originalCommand, FfirstString, FarrayPosition, output);
			}
			return true;
		}

		void parse_error(size_t x, size_t y) {
			debugvisitor("\033[31m\033[7mPARSE ERROR!");
			debugPrintArrayPosition();
			if (visitorCallbacksCompletelySet) {
				visitorCallbackParseError.Execute(originalCommand, FfirstString, FarrayPosition, false);
			}
		}
		void insufficient_bytes(size_t x, size_t y) {
			debugvisitor("\033[31m\033[7mINSUFFICIENT BYTES!");
			debugPrintArrayPosition();
			if (visitorCallbacksCompletelySet) {
				visitorCallbackParseError.Execute(originalCommand, FfirstString, FarrayPosition, true);
			}
		}
	};
};

int connect_to_websocket_server(
	char* text = _strdup("help"),
	char* host = _strdup("localhost"),
	char* port = _strdup("80"),
	bool interactive = false
) {
	//std::cout << "\n\nConnecting to execute command " << text << "\n";
	//print("\n\nConnecting to execute command " + text);

	std::string arguments;
	while (true) {
		// The io_context is required for all I/O
		net::io_context ioc;
		// Launch the asynchronous operation
		std::make_shared<session>(ioc)->run(host, port, text);

		// Run the I/O service. The call will return when
		// the socket is closed.
		ioc.run();
		
		if (!interactive)
			return EXIT_SUCCESS;

		// Do it all again with user input
		/*std::cout << "\nClient inactive>";
		getline(std::cin, arguments);
		text = &arguments[0];*/
		print("Waiting for new user input.\n");
		//text = "console";
		text = "help";

		// If user doesn't specify input, terminate interactive loop
		/*if (arguments.length() == 0)
			return EXIT_SUCCESS;*/
		/*bool QUIT = true;
		if (QUIT == true)
			return EXIT_SUCCESS;*/
	}
}

int connect_to_websocket_serverAdvanced(
	const FReadResponse& Callback,
	char* text = _strdup("help"),
	char* host = _strdup("localhost"),
	char* port = _strdup("80"),
	bool interactive = false
) {
	//std::cout << "\n\nConnecting to execute command " << text << "\n";
	//print("\n\nConnecting to execute command " + text);

	std::string arguments;
	while (true) {
		// The io_context is required for all I/O
		net::io_context ioc;
		// Launch the asynchronous operation
		std::make_shared<session>(ioc)->runAdvanced(Callback, host, port, text);

		// Run the I/O service. The call will return when
		// the socket is closed.
		ioc.run();
		
		if (!interactive)
			return EXIT_SUCCESS;

		// Do it all again with user input
		/*std::cout << "\nClient inactive>";
		getline(std::cin, arguments);
		text = &arguments[0];*/
		print("Waiting for new user input.\n");
		//text = "console";
		text = "help";

		// If user doesn't specify input, terminate interactive loop
		/*if (arguments.length() == 0)
			return EXIT_SUCCESS;*/
		/*bool QUIT = true;
		if (QUIT == true)
			return EXIT_SUCCESS;*/
	}
}

int connect_to_websocket_serverWithAllDelegates(
	const FEndOfConnection& CallbackEndOfConnection,
	const FEndOfReponse& CallbackEndOfReponse,
	const FParseError& CallbackParseError,
	const FStartOrEndOfMap& CallbackStartOrEndOfMap,
	const FStartOrEndOfArray& CallbackStartOrEndOfArray,
	const FFoundAtomNil& CallbackFoundAtomNil,
	const FFoundAtomString& CallbackFoundAtomString,
	const FFoundAtomBinary& CallbackFoundAtomBinary,
	const FFoundAtomExternal& CallbackFoundAtomExternal,
	const FFoundAtomBoolean& CallbackFoundAtomBoolean,
	const FFoundAtomInteger& CallbackFoundAtomInteger,
	const FFoundAtomInteger64& CallbackFoundAtomInteger64,
	const FFoundAtomFloat& CallbackFoundAtomFloat,
	char* text = _strdup("help"),
	char* host = _strdup("localhost"),
	char* port = _strdup("80"),
	bool interactive = false
) {
	//std::cout << "\n\nConnecting to execute command " << text << "\n";
	//print("\n\nConnecting to execute command " + text);

	std::string arguments;
	while (true) {
		// The io_context is required for all I/O
		net::io_context ioc;
		// Launch the asynchronous operation
		std::make_shared<session>(ioc)->runWithAllDelegates(
			CallbackEndOfConnection,
			CallbackEndOfReponse,
			CallbackParseError,
			CallbackStartOrEndOfMap,
			CallbackStartOrEndOfArray,
			CallbackFoundAtomNil,
			CallbackFoundAtomString,
			CallbackFoundAtomBinary,
			CallbackFoundAtomExternal,
			CallbackFoundAtomBoolean,
			CallbackFoundAtomInteger,
			CallbackFoundAtomInteger64,
			CallbackFoundAtomFloat,
			host, port, text);

		// Run the I/O service. The call will return when
		// the socket is closed.
		ioc.run();
		
		if (!interactive)
			return EXIT_SUCCESS;

		// Do it all again with user input
		/*std::cout << "\nClient inactive>";
		getline(std::cin, arguments);
		text = &arguments[0];*/
		print("Waiting for new user input.\n");
		//text = "console";
		text = "help";

		// If user doesn't specify input, terminate interactive loop
		/*if (arguments.length() == 0)
			return EXIT_SUCCESS;*/
		/*bool QUIT = true;
		if (QUIT == true)
			return EXIT_SUCCESS;*/
	}
}

int execute_commands_simultaneously(
	char** commands,
	int numberofcommands,
	char* host = _strdup("localhost"),
	char* port = _strdup("80")
) {
	// create and launch one thread per command
	std::vector<boost::thread*> client_thread_group;
	for (int i = 0; i < numberofcommands; i++) {
		client_thread_group.push_back(
			new boost::thread(
				connect_to_websocket_server, commands[i], host, port, false
			)
		);
	}

	// join and wait for all threads to finish
	for (int i = 0; i < numberofcommands; ++i) {
		client_thread_group[i]->join();
		delete client_thread_group[i];
	}

	// done.
	//std::cout << "Done with all threads. Everything joined.\n";
	print("Done with all threads. Everything joined.");
	return EXIT_SUCCESS;

	// classic execution. this would be successively:
	/*int finalreturncode = EXIT_SUCCESS;
	for (int i = 3; i < argc; i++) {
		text = _strdup(argv[i]);
		std::cout << "\n\nConnecting to execute command " << text << "\n";
		finalreturncode += connect_to_websocket_server(text, host, port);
	}
	return finalreturncode;*/
}

class FNeuralInteractionClient : public INeuralInteractionClient
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	int LoadClient(FString command);
	int LoadClientAdvanced(FString command, const FReadResponse& Callback);
	int LoadClientWithAllDelegates(FString command,
		const FEndOfConnection& CallbackEndOfConnection,
		const FEndOfReponse& CallbackEndOfReponse,
		const FParseError& CallbackParseError,
		const FStartOrEndOfMap& CallbackStartOrEndOfMap,
		const FStartOrEndOfArray& CallbackStartOrEndOfArray,
		const FFoundAtomNil& CallbackFoundAtomNil,
		const FFoundAtomString& CallbackFoundAtomString,
		const FFoundAtomBinary& CallbackFoundAtomBinary,
		const FFoundAtomExternal& CallbackFoundAtomExternal,
		const FFoundAtomBoolean& CallbackFoundAtomBoolean,
		const FFoundAtomInteger& CallbackFoundAtomInteger,
		const FFoundAtomInteger64& CallbackFoundAtomInteger64,
		const FFoundAtomFloat& CallbackFoundAtomFloat
	);

private:
	;
};

IMPLEMENT_MODULE(FNeuralInteractionClient, NeuralInteractionClient)

//int FNeuralInteractionClient::LoadClient() {
int FNeuralInteractionClient::LoadClient(FString command) {
	UE_LOG(NeuralInteractionClient, Log, TEXT("Loading client."));
	char* host;
	char* port;
	char* text;
	host = _strdup("localhost");
	port = _strdup("80");
	//text = _strdup("console");
	text = TCHAR_TO_ANSI(*command);
	connect_to_websocket_server(text, host, port, false);

	int returnValue = 1;
	return returnValue;
}

//int FNeuralInteractionClient::LoadClient() {
int FNeuralInteractionClient::LoadClientWithAllDelegates(FString command,
	const FEndOfConnection& CallbackEndOfConnection,
	const FEndOfReponse& CallbackEndOfReponse,
	const FParseError& CallbackParseError,
	const FStartOrEndOfMap& CallbackStartOrEndOfMap,
	const FStartOrEndOfArray& CallbackStartOrEndOfArray,
	const FFoundAtomNil& CallbackFoundAtomNil,
	const FFoundAtomString& CallbackFoundAtomString,
	const FFoundAtomBinary& CallbackFoundAtomBinary,
	const FFoundAtomExternal& CallbackFoundAtomExternal,
	const FFoundAtomBoolean& CallbackFoundAtomBoolean,
	const FFoundAtomInteger& CallbackFoundAtomInteger,
	const FFoundAtomInteger64& CallbackFoundAtomInteger64,
	const FFoundAtomFloat& CallbackFoundAtomFloat
) {
	UE_LOG(NeuralInteractionClient, Log, TEXT("Loading full delegate client."));
	char* host;
	char* port;
	char* text;
	host = _strdup("localhost");
	port = _strdup("80");
	//text = _strdup("console");
	text = TCHAR_TO_ANSI(*command);
	connect_to_websocket_serverWithAllDelegates(
		CallbackEndOfConnection,
		CallbackEndOfReponse,
		CallbackParseError,
		CallbackStartOrEndOfMap,
		CallbackStartOrEndOfArray,
		CallbackFoundAtomNil,
		CallbackFoundAtomString,
		CallbackFoundAtomBinary,
		CallbackFoundAtomExternal,
		CallbackFoundAtomBoolean,
		CallbackFoundAtomInteger,
		CallbackFoundAtomInteger64,
		CallbackFoundAtomFloat,
		text, host, port, false);

	int returnValue = 1;
	return returnValue;
}

//int FNeuralInteractionClient::LoadClient() {
int FNeuralInteractionClient::LoadClientAdvanced(FString command, const FReadResponse& Callback) {
	UE_LOG(NeuralInteractionClient, Log, TEXT("Loading advanced client."));
	char* host;
	char* port;
	char* text;
	host = _strdup("localhost");
	port = _strdup("80");
	//text = _strdup("console");
	text = TCHAR_TO_ANSI(*command);
	connect_to_websocket_serverAdvanced(Callback, text, host, port, false);

	int returnValue = 1;
	return returnValue;
}

void FNeuralInteractionClient::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	//UE_LOG(NeuralInteractionClient, Log, TEXT("Sarting up\n"));
	UE_LOG(NeuralInteractionClient, Log, TEXT("Starting module FNeuralInteractionClient."));

	FNeuralInteractionClient::LoadClient(FString(TEXT("echo Loaded by StartupModule")));
	//LoadClient();
}

void FNeuralInteractionClient::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

//#undef LOCTEXT_NAMESPACE

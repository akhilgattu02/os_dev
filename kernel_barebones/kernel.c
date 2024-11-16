/*Kernel entry point instead of jumping to kernel.c:0x00*/
void some_function() {
}

int main()
{
	char* video_memory =  0xb8000;
	*video_memory = 'X';
	some_function();
}

void CWE400_Resource_Exhaustion__fgets_sleep_09_bad()
{
    int count;
    /* Initialize count */
    count = MASK_0();
    if(GLOBAL_CONST_TRUE)
    {
        {
            char inputBuffer[CHAR_ARRAY_SIZE] = "";
            /* POTENTIAL FLAW: Read count from the console using fgets() */
            if (NULL != fgets(inputBuffer, CHAR_ARRAY_SIZE, stdin))
            {
                /* Convert to int */
                count = atoi(inputBuffer);
            }
            else
            {
                printLine(MASK_1);
            }
        }
    }
    if(GLOBAL_CONST_TRUE)
    {
        /* POTENTIAL FLAW: Sleep function using count as the parameter with no validation */
        SLEEP(count);
        printLine("Sleep time possibly too long");
    }
}
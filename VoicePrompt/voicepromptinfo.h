#ifndef _VOICEPROMPT_INFO_
#define _VOICEPROMPT_INFO_

#define CONFIGFILENAME                                      "voicepromptconfig.ini"
#define CONFIGFILENAMEBATCH                                 "voicepromptbatchconfig.ini"
#define LANGUAGE_SEPARATOR                                  ";"
#define CONFIG_NEWLINE                                      "\n"
#define CONFIG_NEWLINE1                                     "\r\n"
#define CONFIG_LASTNEWLINE                                  13

#define CONFIG_SPACECHARACTER                               " "

#define CONFIGFILE_VOICEPROMPT_DATA_PREPARE_CONTENT_END     "Voice Prompt Data Prepare Content End"
#define CONFIGFILE_VOICEPROMPT_POS_PREPARE_CONTENT_END      "Voice Prompt pos Prepare Content End"
#define CONFIGFILE_VOICEPROMPT_DATA_PREPARE_CONTENT_BEGIN   "Voice Prompt Data Prepare Content Begin:"
#define CONFIGFILE_VOICEPROMPT_POS_PREPARE_CONTENT_BEGIN    "Voice Prompt Pos Prepare Content Begin:"
#define CONFIGFILE_VOICEPROMPT_DATA_FILENAME                "Voice Prompt Data Filename:"
#define CONFIGFILE_VOICEPROMPT_POS_FILENAME                 "Voice Prompt Pos Filename:"
#define CONFIGFILE_VOICEPROMPT_DATA_VARIABLE_NAME           "Voice Prompt Data Variable:"
#define CONFIGFILE_VOICEPROMPT_POS_VARIABLE_NAME            "Voice Prompt Pos Variable:"

#define CONFIGFILE_LANGUAGE_BEGIN                           "Language Begin:"
#define CONFIGFILE_LANGUAGE_END                             "Language End"

#define CONFIGFILE_LANGUAGE_FILE_END                        "Language File End"

#define CONFIGFILE_ENUM_BEGIN                               "Enum Being:"
#define CONFIGFILE_ENUM_END                                 "Enum End"

#define CONFIGFILE_LANGUAGE_FILE_BEGIN                      "Language File Begin: "

#define CONFIGFILE_DEFINE                                   "#define "
#define CONFIGFILE_UNDEF                                    "#undef "
#define CONFIGFILE_ENDIF                                    "#endif"

#define CONFIGFILE_PLACEFILENAME                            "place.amr"
#define CONFIGFILE_OUTPUTFILENAME                           _T("OutputVoicepromptFiles")
#define CONFIGFILE_UNDERLINE                                _T("_")
#define CONFIGFILE_SEARCHFILE                               _T("\\*.*")
#define CONFIGFILE_CSTRINGSLASH                             _T("\\")
#define CONFIGFILE_ACCESSIONALFILEPATULOUSNAME              ".ini"
#define CONFIGFILE_FILESIZEINFORMATION                      "_files_size.ini"

#define CONFIGFILE_COMMENTDEFINE                            "//#define "
#define CONFIGFILE_INDEF                                    "#ifdef "

#define CONFIGFILE_AUTOSELECTLANGUAGE
#define CONFIGFILE_AUTOFILEINDEX                            8

#define CONFIGFILE_SILENTFILESIZE                           71
////////////////////////////////////////////////////////////////////////
#define CONFIGFILE_BATCH_CHOOSELANGUAGEFOLDBEGIN            "Batch Output Choose Language Fold Begin"
#define CONFIGFILE_BATCH_CHOOSELANGUAGEFOLDEND              "Batch Output Choose Language Fold End"
#define CONFIGFILE_BATCH_OUTPUTROOTFOLDBEGIN                "Batch Output Language Root Fold Begin"
#define CONFIGFILE_BATCH_OUTPUTROOTFOLDEND                  "Batch Output Language Root Fold End"

#define CONFIGFILE_BATCH_ITEMBEGIN                          "Batch Output Languages Begin"
#define CONFIGFILE_BATCH_ITEMEND                            "Batch Output Languages End"

#define CONFIGFILE_QUOTATION                                "\""

#define CONFIGFILE_PACKSIZELIMITION                         (150 * 1024)
#define CONFIGFILE_KUNIT                                    (1024.0)

#define CONFIGFILE_BATCHOUTPUT                              "config.ini"

typedef enum
{
    BATCH_SCAN_CHOOSEFOLD,
    BATCH_SCAN_ROOTFOLD,
    BATCH_SCAN_NONE
}BATCH_SCAN_TYPE;

DWORD VoicePromptGetFileSize(CString cFilename);
BOOL CreateDirectoryFromString(CString csPath);
CString GetCurrentAppPath(void);
BOOL FileIfExist(CString cFilename);
CString GetBatchOutputLanguage(CString cLanguages);

#endif//_VOICEPROMPT_INFO_

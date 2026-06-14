execute_process(COMMAND git rev-list --count HEAD 
    OUTPUT_VARIABLE GIT_COMMIT_COUNT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)

execute_process(COMMAND git status --porcelain 
COMMAND grep "^ M"
OUTPUT_VARIABLE GIT_MODIFIED_FILES
OUTPUT_STRIP_TRAILING_WHITESPACE
ERROR_QUIET
)

message(STATUS "====================================================")
message(STATUS "Git commit count: ${GIT_COMMIT_COUNT}")
message(STATUS "Modified files:\n${GIT_MODIFIED_FILES}")
message(STATUS "====================================================")
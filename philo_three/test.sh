#!/usr/bin/env bash

YELLOW="\033[0;33m"
RESET_COLOR="\033[0m"
RED="\033[0;31m"
BOLD="\033[1m"
GREEN="\033[0;32m"

# Decorator
function @ {
  printf $BOLD"[$I] $1\n" | tr '_' ' '
  ((I++))
  eval $1 $@
  printf $RESET_COLOR
}

function    Testing_bad_input() {
  ERROR=0
  function check_error_args() {
    STDERR=$(eval $e 2>&1 >/dev/null);
    if [[ ! $STDERR ]] || [[ ! $? ]] ; then
      ((ERROR++))
      printf $RED
      printf "\tERROR : $e Stdeer or function return isn\'t set\n"
      printf $RESET_COLOR
    fi
  }
  for e in "${BAD_INPUT[@]}"; do
    check_error_args
  done
  if [[ $ERROR != 0 ]]; then
    printf $RED
    printf "\n\t$ERROR occurred\n"
    printf $RESET_COLOR
  fi
  ((TOTAL_ERRORS+=$ERROR))
}

I=0;
TOTAL_ERRORS=0
declare -a BAD_INPUT=(
  "./philo_one 10 52 054e 4 "
  "./philo_one 10000 52 54 44 0 15"
  "./philo_one 1 5"
  "./philo_one 1 5 48 2545 48 21 7"
)
@ Testing_bad_input $@;


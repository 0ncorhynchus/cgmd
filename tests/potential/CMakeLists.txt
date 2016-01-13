set(TEST_NAMES
    fene_bond_potential_test
    harmonic_bond_potential_test
    lennard_jones_potential_test
    lowest_order_harmonic_bend_potential_test
    tails_attraction_potential_test
    weeks_chandler_anderson_potential_test
    )

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
set(test_libraries
    pthread
    ${GTEST_BOTH_LIBRARIES}
)

foreach(TEST_NAME ${TEST_NAMES})
    add_executable(${TEST_NAME} ${TEST_NAME}.cpp)
    target_link_libraries(${TEST_NAME} cgmd ${test_libraries})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach(TEST_NAME)


pipeline {
    agent any

    environment {
        PATH = "$WORKSPACE/cmake-bin/bin:$WORKSPACE/compiler/bin:$PATH"
    }

    stages {
        stage('Prepare Environment') {
            steps {
                sh '''
                # Create directories for binaries
                mkdir -p $WORKSPACE/cmake-bin
                mkdir -p $WORKSPACE/compiler

                # Download pre-built CMake binary
                curl -LO https://github.com/Kitware/CMake/releases/download/v3.26.4/cmake-3.26.4-linux-aarch64.tar.gz
                tar -xvf cmake-3.26.4-linux-aarch64.tar.gz --strip-components=1 -C $WORKSPACE/cmake-bin

                # Download GCC binary
                curl -LO https://developer.arm.com/-/media/Files/downloads/gnu/12.2-2022.09/binrel/gcc-arm-12.2-2022.09-x86_64-aarch64-none-linux-gnu.tar.xz
                tar -xvf gcc-arm-12.2-2022.09-x86_64-aarch64-none-linux-gnu.tar.xz --strip-components=1 -C $WORKSPACE/compiler

                # Debug
                echo "Checking GCC setup"
                ls -al $WORKSPACE/compiler/bin
                export PATH=$WORKSPACE/compiler/bin:$PATH
                which gcc
                gcc --version
                '''
            }
        }

        stage('Debug PATH and CMake Version') {
            steps {
                sh '''
                echo "Current PATH: $PATH"
                which cmake
                cmake --version
                which gcc
                gcc --version || echo "GCC not found or not executable"
                '''
            }
        }

        stage('Checkout Code') {
            steps {
                git 'https://github.com/gopuman/Jenkins-cmake-test'
            }
        }

        stage('Configure and Build') {
            steps {
                sh '''
                mkdir -p build
                cd build
                cmake -DCMAKE_C_COMPILER=$WORKSPACE/compiler/bin/gcc -DCMAKE_CXX_COMPILER=$WORKSPACE/compiler/bin/g++ ..
                make
                '''
            }
        }

        stage('Run Tests') {
            steps {
                sh '''
                cd build
                ctest --verbose
                '''
            }
        }

        stage('Archive Artifacts') {
            steps {
                archiveArtifacts artifacts: 'build/**', fingerprint: true
            }
        }
    }

    post {
        always {
            echo 'Pipeline completed.'
        }
        failure {
            echo 'Pipeline failed!'
        }
    }
}

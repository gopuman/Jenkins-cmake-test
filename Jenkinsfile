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

                # Download pre-built GCC binary from musl.cc
                curl -LO https://musl.cc/aarch64-linux-musl-cross.tgz
                tar -xvf aarch64-linux-musl-cross.tgz --strip-components=1 -C $WORKSPACE/compiler

                # Debug files
                echo "Listing GCC directory:"
                ls -al $WORKSPACE/compiler/bin

                # Add GCC to PATH
                export PATH=$WORKSPACE/compiler/bin:$PATH
                which gcc
                gcc --version || echo "GCC not executable"
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

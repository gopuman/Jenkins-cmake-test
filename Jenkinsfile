pipeline {
    agent any

    environment {
        PATH = "$WORKSPACE/cmake-bin:$PATH"
    }

    stages {
        stage('Install CMake from Source') {
            steps {
                sh '''
                # Install dependencies for building CMake
                apt-get update && apt-get install -y build-essential libssl-dev

                # Download and extract CMake source
                curl -LO https://github.com/Kitware/CMake/releases/download/v3.26.4/cmake-3.26.4.tar.gz
                tar -xvf cmake-3.26.4.tar.gz
                cd cmake-3.26.4

                # Compile and install CMake
                ./bootstrap --prefix=$WORKSPACE/cmake-bin
                make -j$(nproc)
                make install
                cd ..
                '''
            }
        }

        stage('Debug PATH and CMake Version') {
            steps {
                sh '''
                echo "Current PATH: $PATH"
                which cmake
                cmake --version
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
                cmake ..
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

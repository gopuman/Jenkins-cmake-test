pipeline {
    agent any

    stages {
        stage('Install CMake') {
            steps {
                sh '''
                # Download and extract CMake using curl
                curl -LO https://github.com/Kitware/CMake/releases/download/v3.26.4/cmake-3.26.4-linux-x86_64.tar.gz
                tar -xvf cmake-3.26.4-linux-x86_64.tar.gz
                export PATH=$PWD/cmake-3.26.4-linux-x86_64/bin:$PATH
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
            echo 'Build failed.'
        }
    }
}

FROM debian:11

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
      ca-certificates \
      apt-transport-https \
      gnupg \
      sudo \
      build-essential \
      git \
      qemu-system-misc \
      gdb-multiarch \
      gcc-riscv64-unknown-elf && \
    rm -rf /var/lib/apt/lists/*

ARG USER=dev
ARG UID=1000
RUN useradd -m -u ${UID} -s /bin/bash ${USER} && \
    echo "${USER} ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/${USER} && \
    chmod 0440 /etc/sudoers.d/${USER}

WORKDIR /home/${USER}
USER ${USER}
ENV HOME=/home/${USER}
CMD ["/bin/bash"]
